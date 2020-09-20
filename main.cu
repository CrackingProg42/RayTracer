
#define inf 1e9
#define eps 1e-6

#include <fstream>
#include <iostream>


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <ctime>
#include <vector>
#include <string>
#include <unordered_map>
#include <random>
#include <cstdint>
#include <algorithm>
#include <curand_kernel.h>
#include <curand.h>
#include <time.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <thrust/sort.h>

#include <stdio.h>
#include <cmath>

#define DEVICE __host__ __device__

#define checkCudaErrors(val) check_cuda( (val), #val, __FILE__, __LINE__ )

void check_cuda(cudaError_t result, char const* const func, const char* const file, int const line) {
	if (result) {
		std::cerr << "CUDA error = " << static_cast<unsigned int>(result) << " at " <<
			file << ":" << line << " '" << func << "' \n";
		// Make sure we call CUDA Device Reset before exiting
		cudaDeviceReset();
		exit(99);
	}
}


struct Vec {
public:
	double x, y, z;
	DEVICE Vec(double x0, double y0, double z0) : x(x0), y(y0), z(z0) {}
	DEVICE Vec() : x(0), y(0), z(0) {}
	DEVICE Vec(double d) : x(d), y(d), z(d) {}
	DEVICE Vec operator+(const Vec& b) const { return Vec(x + b.x, y + b.y, z + b.z); }
	DEVICE Vec operator-(const Vec& b) const { return Vec(x - b.x, y - b.y, z - b.z); }
	DEVICE Vec operator*(double b) const { return Vec(x * b, y * b, z * b); }
	DEVICE Vec operator/(double b) const { return Vec(x / b, y / b, z / b); }
	DEVICE Vec operator*(const Vec& b) const { return Vec(x * b.x, y * b.y, z * b.z); }
	DEVICE Vec& norm() { return *this = *this / length(); }
	DEVICE double length() { return sqrt(x * x + y * y + z * z); }
	DEVICE double dot(const Vec& b) const { return x * b.x + y * b.y + z * b.z; }
	DEVICE Vec operator%(Vec& b) const { return Vec(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x); }
	DEVICE bool operator!=(const Vec& b) const { return (b.x != x || b.y != y || b.z != z); }
};

struct Ray {
	Vec o, d;
	DEVICE Ray(Vec o0 = 0, Vec d0 = 0) { o = o0, d = d0.norm(); }
};

#include <algorithm>

struct AABB {
	DEVICE inline AABB() { min = Vec(inf, inf, inf); max = Vec(-inf, -inf, -inf); }	// an empty interval
	DEVICE inline AABB(Vec min_, Vec max_) { min = min_; max = max_; }
	DEVICE inline bool unbounded() const { return min.x == -inf || min.y == -inf || min.z == -inf || max.x == inf || max.y == inf || max.z == inf; }
	DEVICE inline size_t largestDimension() const {
		double dx = abs(max.x - min.x);
		double dy = abs(max.y - min.y);
		double dz = abs(max.z - min.z);
		if (dx > dy && dx > dz) {
			return 0;
		}
		if (dy > dz) {
			return 1;
		}
		return 2;
	}

	// ray-slab tests, see PBRT 2nd edition, section 4.2.1
	DEVICE inline bool intersect(const Ray& ray, const Vec& inverseDirection, double closestKnownT) const {
		bool xDirNegative = ray.d.x < 0;
		bool yDirNegative = ray.d.y < 0;
		bool zDirNegative = ray.d.z < 0;

		// check for ray intersection against x and y slabs
		float tmin = ((xDirNegative ? max.x : min.x) - ray.o.x) * inverseDirection.x;
		float tmax = ((xDirNegative ? min.x : max.x) - ray.o.x) * inverseDirection.x;
		float tymin = ((yDirNegative ? max.y : min.y) - ray.o.y) * inverseDirection.y;
		float tymax = ((yDirNegative ? min.y : max.y) - ray.o.y) * inverseDirection.y;
		if (tmin > tymax || tymin > tmax) {
			return false;
		}
		if (tymin > tmin) {
			tmin = tymin;
		}
		if (tymax < tmax) {
			tmax = tymax;
		}

		// check for ray intersection against z slab
		float tzmin = ((zDirNegative ? max.z : min.z) - ray.o.z) * inverseDirection.z;
		float tzmax = ((zDirNegative ? min.z : max.z) - ray.o.z) * inverseDirection.z;
		if (tmin > tzmax || tzmin > tmax) {
			return false;
		}
		if (tzmin > tmin) {
			tmin = tzmin;
		}
		if (tzmax < tmax) {
			tmax = tzmax;
		}
		return (tmin < closestKnownT) && (tmax > eps);
	}

	Vec min;
	Vec max;
};

DEVICE double mini(double a, double b) {
	if (a < b)
		return a;
	return b;
}


DEVICE double maxi(double a, double b) {
	if (a > b)
		return a;
	return b;
}

DEVICE inline AABB enclose(const AABB& firstBoundingBox, const AABB& secondBoundingBox) {
	AABB ret;

	ret.min.x = mini(firstBoundingBox.min.x, secondBoundingBox.min.x);
	ret.min.y = mini(firstBoundingBox.min.y, secondBoundingBox.min.y);
	ret.min.z = mini(firstBoundingBox.min.z, secondBoundingBox.min.z);

	ret.max.x = maxi(firstBoundingBox.max.x, secondBoundingBox.max.x);
	ret.max.y = maxi(firstBoundingBox.max.y, secondBoundingBox.max.y);
	ret.max.z = maxi(firstBoundingBox.max.z, secondBoundingBox.max.z);

	return ret;
}

DEVICE inline AABB enclose(const AABB& boundingBox, const Vec& point) {
	AABB ret;

	ret.min.x = mini(boundingBox.min.x, point.x);
	ret.min.y = mini(boundingBox.min.y, point.y);
	ret.min.z = mini(boundingBox.min.z, point.z);

	ret.max.x = maxi(boundingBox.max.x, point.x);
	ret.max.y = maxi(boundingBox.max.y, point.y);
	ret.max.z = maxi(boundingBox.max.z, point.z);

	return ret;
}

# define RND2(state) (float)curand_uniform(&state)
# define RND(state) (2.0*RND2(state))-1.0

#define PI 3.1415926536

int width, height;
using namespace std;
typedef unordered_map<string, double> pl;

// create an orthonormal system, assuming v1 is already normalized
DEVICE void ons(const Vec& v1, Vec& v2, Vec& v3) {
	if (std::abs(v1.x) > std::abs(v1.y)) {
		// project to the y = 0 plane and construct a normalized orthogonal vector in this plane
		float invLen = 1.f / sqrtf(v1.x * v1.x + v1.z * v1.z);
		v2 = Vec(-v1.z * invLen, 0.0f, v1.x * invLen);
	}
	else {
		// project to the x = 0 plane and construct a normalized orthogonal vector in this plane
		float invLen = 1.0f / sqrtf(v1.y * v1.y + v1.z * v1.z);
		v2 = Vec(0.0f, v1.z * invLen, -v1.y * invLen);
	}
	v3 = v1 % v2;
}

void render(Vec* pix, int s) {
	fstream myfile;
	std::cout << "iter " << s << std::endl;
	myfile.open("render.ppm", fstream::out);
	myfile << "P3\n" << width << " " << height << "\n255\n";
	for (int col = 0; col < width; col++) {
		for (int row = 0; row < height; row++) {
			int pixel_index = row * width + col;
			myfile << std::min((int)(pix[pixel_index].x / (float)(s + 1)), 255) << " ";
			myfile << std::min((int)(pix[pixel_index].y / (float)(s + 1)), 255) << " ";
			myfile << std::min((int)(pix[pixel_index].z / (float)(s + 1)), 255) << std::endl;
		}
	}
}
// Objects have color, emission, type (diffuse, specular, refractive)
// All object should be intersectable and should be able to compute their surface normals.
class Obj {
public:
	Vec cl;
	Vec emission;
	int type;
	DEVICE void setMat(Vec color_ = Vec(), Vec emission_ = 0, int type_ = 0) { cl = color_; emission = emission_; type = type_; }
	DEVICE virtual double intersect(const Ray&) const = 0;
	DEVICE virtual Vec normal(const Vec&) const = 0;
	DEVICE virtual AABB getAABB() const = 0;
};

class Plane : public Obj {
public:
	Vec n;
	double d;
	DEVICE Plane(double d_ = 0, Vec n_ = 0) {
		d = d_;
		n = n_;
	}
	DEVICE double intersect(const Ray& ray) const {
		double d0 = n.dot(ray.d);
		if (d0 != 0) {
			double t = -1 * (((n.dot(ray.o)) + d) / d0);
			return (t > eps) ? t : 0;
		}
		else return 0;
	}
	DEVICE Vec normal(const Vec& p0) const { return n; }
	DEVICE AABB getAABB() const {
		if (n.x == 0 && n.y == 0) return AABB(Vec(-inf, -inf, d * n.z), Vec(inf, inf, d * n.z));
		if (n.x == 0 && n.z == 0) return AABB(Vec(-inf, d * n.y, -inf), Vec(inf, d * n.y, inf));
		if (n.y == 0 && n.z == 0) return AABB(Vec(d * n.x, -inf, -inf), Vec(d * n.x, inf, inf));
		return AABB(Vec(-inf, -inf, -inf), Vec(inf, inf, inf));
	}
};

class Sphere : public Obj {
public:
	Vec c;
	double r;

	DEVICE Sphere(double r_ = 0, Vec c_ = 0) { c = c_; r = r_; }
	DEVICE double intersect(const Ray& ray) const {
		double b = ((ray.o - c) * 2).dot(ray.d);
		double c_ = (ray.o - c).dot((ray.o - c)) - (r * r);
		double disc = b * b - 4 * c_;
		if (disc < 0) return 0;
		else disc = sqrt(disc);
		double sol1 = -b + disc;
		double sol2 = -b - disc;
		return (sol2 > eps) ? sol2 / 2 : ((sol1 > eps) ? sol1 / 2 : 0);
	}

	DEVICE Vec normal(const Vec& p0) const {
		return (p0 - c).norm();
	}
	DEVICE AABB getAABB() const {
		return AABB(Vec(c.x - r, c.y - r, c.z - r), Vec(c.x + r, c.y + r, c.z + r));
	}
};

class Intersection {
public:
	DEVICE Intersection() { t = inf; object = nullptr; }
	DEVICE Intersection(double t_, Obj* object_) { t = t_; object = object_; }
	DEVICE operator bool() { return object != nullptr; }
	double t;
	Obj* object;
};

class Scene {
	Obj** objects;
	int list_size;

public:

	DEVICE Scene() {}

	DEVICE Scene(Obj** objs, int size) {
		objects = objs;
		list_size = size;
	}

	DEVICE Intersection intersect(const Ray& ray) const {
		Intersection closestIntersection;
		// intersect all objects, one after the other
		for (int i = 0; i < list_size; i++) {
			Intersection inter = Intersection(objects[i]->intersect(ray), objects[i]);
			if (inter.t > eps && inter.t < closestIntersection.t) {
				closestIntersection = inter;
			}
		}

		return closestIntersection;
	}
};

class 	Data {
public:
	int type;
	Vec clr;
	double cost;
	Vec emission;

	DEVICE Data(int t = 0, Vec cl = Vec(0), double co = 0, Vec em = Vec(0)) { type = t; clr = cl; cost = co, emission = em; }
};

// Class for generating the Halton low-discrepancy series for Quasi
// Monte Carlo integration.
class Halton {
	double value, inv_base;
public:
	DEVICE void number(int i, int base) {
		double f = inv_base = 1.0 / base;
		value = 0.0;
		while (i > 0) {
			value += f * (double)(i % base);
			i /= base;
			f *= inv_base;
		}
	}
	DEVICE void next() {
		double r = 1.0 - value - 0.0000001;
		if (inv_base < r) value += inv_base;
		else {
			double h = inv_base, hh;
			do { hh = h; h *= inv_base; } while (h >= r);
			value += hh + h - 1.0;
		}
	}
	DEVICE double get() { return value; }
};

// Input is the pixel offset, output is the appropriate coordinate
// on the image plane
DEVICE Vec camcr(const double x, const double y, int width, int height) {
	double w = width;
	double h = height;
	float fovx = PI / 4;
	float fovy = (h / w) * fovx;
	return Vec(((2 * x - w) / w) * tan(fovx),
		-((2 * y - h) / h) * tan(fovy),
		-1.0);
}

// Uniform sampling on a hemisphere to produce outgoing ray directions.
// courtesy of http://www.rorydriscoll.com/2009/01/07/better-sampling/
DEVICE Vec hemisphere(double u1, double u2) {
	const double r = sqrt(1.0 - u1 * u1);
	const double phi = 2 * PI * u2;
	return Vec(cos(phi) * r, sin(phi) * r, u1);
}

__device__ void trace(Data* clrlist, Ray& ray, Scene** scene, Vec& clr, float& refr_ind, const int bounce_max, curandState localState, int penetration_index) {
	// Russian roulette: starting at depth 5, each recursive step will stop with a probability of 0.1
	Data dt;
	Vec tmp;
	Intersection intersection;
	Vec hp;
	Vec N;
	Vec rotX, rotY;
	Vec sampledDir;
	Vec rotatedDir;

	int iter = 0;
	double cost;
	double rrFactor = 1.0;
	double n;
	double R0;
	double cost1;
	double cost2;
	double Rprob;
	const double rrStopProbability = 0.1;
	for (int depth = 0; depth < bounce_max; depth++) {
		if (depth >= 5) {
			if ((RND2(localState)) <= rrStopProbability) {
				break;
			}
			rrFactor = 1.0 / (1.0 - rrStopProbability);
		}

		intersection = (*scene)->intersect(ray);

		if (!intersection) break;

		// Travel the ray to the hit point where the closest object lies and compute the surface normal there.
		hp = ray.o + ray.d * intersection.t;
		N = intersection.object->normal(hp);
		ray.o = hp;

		// Add the emission, the L_e(x,w) part of the rendering equation, but scale it with the Russian Roulette
		// probability weight.
		const Vec emission = intersection.object->emission;
		tmp = emission * rrFactor;

		// Diffuse BRDF - choose an outgoing direction with hemisphere sampling.
		if (intersection.object->type == 1) {
			ons(N, rotX, rotY);
			sampledDir = hemisphere((RND2(localState)), (RND2(localState)));
			rotatedDir.x = Vec(rotX.x, rotY.x, N.x).dot(sampledDir);
			rotatedDir.y = Vec(rotX.y, rotY.y, N.y).dot(sampledDir);
			rotatedDir.z = Vec(rotX.z, rotY.z, N.z).dot(sampledDir);
			ray.d = rotatedDir;	// already normalized
			cost = ray.d.dot(N);
			dt = Data(1, intersection.object->cl, cost, tmp);
		}

		// Specular BRDF - this is a singularity in the rendering equation that follows
		// delta distribution, therefore we handle this case explicitly - one incoming
		// direction -> one outgoing direction, that is, the perfect reflection direction.
		if (intersection.object->type == 2) {
			cost = ray.d.dot(N);
			ray.d = (ray.d - N * (cost * 2)).norm();
			dt = Data(2, intersection.object->cl, cost, tmp);
		}

		// Glass/refractive BRDF - we use the vector version of Snell's law and Fresnel's law
		// to compute the outgoing reflection and refraction directions and probability weights.
		if (intersection.object->type == 3) {
			n = refr_ind;
			R0 = (1.0 - n) / (1.0 + n);
			R0 = R0 * R0;
			if (N.dot(ray.d) > 0) { // we're inside the medium
				N = N * -1;
				n = 1 / n;
			}
			n = 1 / n;
			cost1 = (N.dot(ray.d)) * -1; // cosine of theta_1
			cost2 = 1.0 - n * n * (1.0 - cost1 * cost1); // cosine of theta_2
			Rprob = R0 + (1.0 - R0) * pow(1.0 - cost1, 5.0); // Schlick-approximation
			if (cost2 > 0 && (RND2(localState)) > Rprob) { // refraction direction
				ray.d = ((ray.d * n) + (N * (n * cost1 - sqrt(cost2)))).norm();
			}
			else { // reflection direction
				ray.d = (ray.d + N * (cost1 * 2)).norm();
			}
			dt = Data(3, intersection.object->cl, cost1, tmp);
		}

		clrlist[bounce_max - depth - 1] = dt;
		iter++;
	}
	for (int i = bounce_max - iter; i < bounce_max; i++) {
		if (clrlist[i].type == 1) {
			clr = clrlist[i].emission + (clr * clrlist[i].clr) * clrlist[i].cost * 0.1 * rrFactor;
		}
		if (clrlist[i].type == 2) {
			clr = clrlist[i].emission + clr * rrFactor;
		}
		if (clrlist[i].type == 3) {
			if (i == bounce_max - 1 || (i - 2 >= 0 && clrlist[i - 2].emission != Vec(0)))
				clr = clrlist[i].emission + (clr * clrlist[i].clr) * 1.15 * rrFactor;
			else
				clr = clrlist[i].emission + clr * 1.15 * rrFactor;
		}
	}
}


__global__ void calc_render(int spt, int bounce_max, Data* clrlist, float refr_ind, int spp, Scene** scene, Vec* pix, curandState* rand_state, int actual, int width, int height, int penetration_index) {
	int row = threadIdx.x + blockIdx.x * blockDim.x;
	int col = threadIdx.y + blockIdx.y * blockDim.y;
	if ((col >= width) || (row >= height)) return;
	int pixel_index = col * width + row;
	curand_init((double)((actual + 1) * pixel_index), pixel_index, 0, &rand_state[pixel_index]);
	for (int s = 0; s < spt; s++) {
		//curandState localState = rand_state[pixel_index];
		Vec clr = Vec(0, 0, 0);
		Ray ray;
		ray.o = (Vec(0, 0, 0)); // rays start out from here
		Vec cam = camcr(col, row, width, height); // construct image plane coordinates
		cam.x = cam.x + (RND(rand_state[pixel_index])) / 700; // anti-aliasing for free
		cam.y = cam.y + (RND(rand_state[pixel_index])) / 700;
		ray.d = (cam - ray.o).norm(); // point from the origin to the camera plane
		trace(&(clrlist[pixel_index * bounce_max]), ray, scene, clr, refr_ind, bounce_max, rand_state[pixel_index], penetration_index);
		pix[pixel_index] = pix[pixel_index] + clr;
	}
}

__global__ void create_world(Obj** d_list, int size, Scene** d_scene) {
	d_list[0] = new Sphere(1.05, Vec(-0.75, -1.45, -4.4));
	d_list[0]->setMat(Vec(4, 8, 4), Vec(0), 2);

	d_list[1] = new Sphere(0.5, Vec(2.0, -2.05, -3.7));
	d_list[1]->setMat(Vec(1, 1, 1), Vec(0), 3);

	d_list[2] = new Sphere(0.6, Vec(-1.75, -1.95, -3.1));
	d_list[2]->setMat(Vec(4, 4, 12), Vec(0), 1);

	d_list[3] = new Plane(2.5, Vec(0, 1, 0));
	d_list[3]->setMat(Vec(6, 6, 6), Vec(0), 1);

	d_list[4] = new Plane(5.5, Vec(0, 0, 1));
	d_list[4]->setMat(Vec(6, 6, 6), Vec(0), 1);

	d_list[5] = new Plane(2.75, Vec(1, 0, 0));
	d_list[5]->setMat(Vec(10, 2, 2), Vec(0), 1);

	d_list[6] = new Plane(2.75, Vec(-1, 0, 0));
	d_list[6]->setMat(Vec(2, 10, 2), Vec(0), 1);

	d_list[7] = new Plane(3.0, Vec(0, -1, 0));
	d_list[7]->setMat(Vec(6, 6, 6), Vec(0), 1);

	d_list[8] = new Plane(0.5, Vec(0, 0, -1));
	d_list[8]->setMat(Vec(6, 6, 6), Vec(0), 1);

	d_list[9] = new Sphere(0.5, Vec(0, 0.5, -2));
	d_list[9]->setMat(Vec(2, 2, 10), Vec(0), 2);

	d_list[10] = new Sphere(0.5, Vec(0, 1.9, -3));
	d_list[10]->setMat(Vec(2, 2, 10), Vec(5000, 2000, 2000), 1);

	*d_scene = new Scene(d_list, size);
}

void render(int id, int size, int spp, double refr_index, int spt) {
	srand(time(NULL));
	int tx = 16;
	int ty = 16;
	int bounce_max = 7;
	int obj_num = 11;
	int penetration_index = 1;

	Obj** list;
	cudaMalloc((void**)&list, obj_num * sizeof(Obj*));
	Scene** scene;
	cudaMalloc((void**)&scene, sizeof(Scene*));

	create_world<<<1, 1>>>(list, obj_num, scene);
	checkCudaErrors(cudaGetLastError());
	checkCudaErrors(cudaDeviceSynchronize());

	width = size;
	height = size;

	dim3 blocks(width / tx + 1, height / ty + 1);
	dim3 threads(tx, ty);
	
	Vec* d_pix;
	cudaMalloc((void**)&d_pix, width * height * sizeof(Vec));
	Vec* h_pix = (Vec*)malloc(width * height * sizeof(Vec));
	
	curandState* d_rand_state;
	cudaMalloc((void**)&d_rand_state, width * height * sizeof(curandState));
	Data* clrlist;
	cudaMalloc((void**)&clrlist, sizeof(Data) * bounce_max * width * height);

	checkCudaErrors(cudaGetLastError());
	checkCudaErrors(cudaDeviceSynchronize());

	// correlated Halton-sequence dimensions
	Halton hal, hal2;
	hal.number(0, 2);
	hal2.number(0, 2);

	bool running = true;

	for (int s = 0; s < spp; s += spt) {
		if (running) {
			calc_render<<<blocks, threads>>>(spt, bounce_max, clrlist, refr_index, spp, scene, d_pix, d_rand_state, s, width, height, penetration_index);
			checkCudaErrors(cudaGetLastError());
			checkCudaErrors(cudaDeviceSynchronize());
		}
		if (!running) return;
		cudaMemcpy(h_pix, d_pix, width * height * sizeof(Vec), cudaMemcpyDeviceToHost);
		render(h_pix, s + spt);
	}
	cudaFree(d_rand_state);
}

int main() {
	render(1, 600, 1000, 1.5, 100);
}
