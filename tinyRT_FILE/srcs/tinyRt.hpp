

#ifndef TINYRT_HPP
#define TINYRT_HPP

#include <cstdio>
#include <cmath>
#include <random>
#include <deque>
#include <map>
#include <time.h>
#include <iostream>

#ifdef __CUDACC__
#define DEVICE  __host__ __device__
#define GLOBAL __global__
#else
#define DEVICE
#define GLOBAL
using namespace std;
#define RND (2.0*((double) std::rand() / (RAND_MAX))-1.0)
#define RND2 ((double) std::rand() / (RAND_MAX))
#endif

#define inf 1e9
#define eps 1e-6

#define PI 3.1415926536
#define W 200
#define H 200
#define BLOCK_SIZE 5

typedef std::map<std::string, double> pl;

class Vector3 {
public:
    double x, y, z;
    DEVICE Vector3(double x0, double y0, double z0) : x(x0), y(y0), z(z0) {}
    DEVICE Vector3() : x(0), y(0), z(0) {}
    DEVICE Vector3(double d) : x(d), y(d), z(d) {}
    DEVICE Vector3 operator+(const Vector3 &b) const { return Vector3(x+b.x, y+b.y, z+b.z); }
    DEVICE Vector3 operator-(const Vector3 &b) const { return Vector3(x-b.x, y-b.y, z-b.z); }
    DEVICE Vector3 operator*(double b) const { return Vector3(x*b, y*b, z*b); }
    DEVICE Vector3 operator/(double b) const { return Vector3(x/b, y/b, z/b); }
    DEVICE Vector3 operator*(const Vector3 &b) const { return Vector3(x*b.x, y*b.y, z*b.z); }
    DEVICE Vector3& norm() { return *this = *this / length(); }
    DEVICE double length() { return sqrt(x*x+y*y+z*z); }
    DEVICE double dot(const Vector3 &b) const { return x*b.x+y*b.y+z*b.z; }
    DEVICE Vector3 operator%(Vector3 &b) const { return Vector3(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x); }
};

// Rays have origin and direction.
// The direction Vector3tor should always be normalized.
class Ray {
public:
    Vector3 o, d;
    DEVICE Ray(Vector3 o0 = Vector3(), Vector3 d0 = Vector3()) : o(o0), d(d0) {}
};

// Objects have color, emission, type (diffuse, specular, refractive)
// All object should be intersectable and should be able to compute their surface normals.
class Object {
public:
    Vector3 color;
    double emission;
    int type; //
    DEVICE void setMat(Vector3 color_ = Vector3(), double emission_ = 0, int type_=0) { color = color_; emission = emission_; type = type_; }
    DEVICE virtual double intersect(const Ray&) const = 0;
    DEVICE virtual Vector3 normal(const Vector3&) const = 0;
};

class Sphere : public Object {
public:
	Vector3 c;
	double r;

	DEVICE Sphere(double r_ = 0, Vector3 c_ = 0) : c(c_), r(r_) {}
	DEVICE virtual double intersect(const Ray& ray) const {
		double b = ((ray.o - c) * 2).dot(ray.d);
		double c_ = (ray.o - c).dot((ray.o - c)) - (r*r);
		double disc = b*b - 4 * c_;
		if (disc < 0) return 0;
		else disc = sqrt(disc);
		double sol1 = -b + disc;
		double sol2 = -b - disc;
		return (sol2 > eps) ? sol2 / 2 : ((sol1 > eps) ? sol1 / 2 : 0);
	}

	DEVICE virtual Vector3 normal(const Vector3& p0) const {
		return (p0 - c).norm();
	}
};

class Plane : public Object {
public:
	Vector3 n;
	double d;
	DEVICE Plane(double d_ = 0, Vector3 n_ = 0) : d(d_), n(n_) {}
	DEVICE virtual double intersect(const Ray& ray) const {
		double d0 = n.dot(ray.d);
		if (d0 != 0) {
			double t = -1 * (((n.dot(ray.o)) + d) / d0);
			return (t > eps) ? t : 0;
		} else return 0;
	}
	DEVICE virtual Vector3 normal(const Vector3& p0) const { return n; }
};

class Intersection {
public:
	DEVICE Intersection() : t(inf), obj(nullptr) {}
	DEVICE Intersection(double t_, Object* obj_) : t(t_), obj(obj_) {}
	DEVICE operator bool() { return obj != nullptr; }
	double t;
	Object* obj;
};

class Scene {
	Object** objects;
	int list_size;

public:
	DEVICE Scene() {}

	DEVICE Scene(Object** objs, int size) {
		objects = objs;
		list_size = size;
	}

	DEVICE Intersection intersect(const Ray& ray) const{
		Intersection closestIntersection;
		// intersect all objects, one after the other
		for (int i = 0; i < list_size; i++) {
			double t = objects[i]->intersect(ray);
			if (t > eps && t < closestIntersection.t) {
				closestIntersection.t = t;
				closestIntersection.obj = objects[i];
			}
		}
		return closestIntersection;
	}
};

class 	Data {
public:
	int type;
	Vector3 clr;
	double cost;
	Vector3 emission;

	DEVICE Data(int t=0, Vector3 cl=Vector3(0), double co=0, Vector3 em=Vector3(0)) {type = t; clr = cl; cost = co, emission = em;}
};

GLOBAL Vector3 camCastRay(const double x, const double y);
GLOBAL Vector3 hemisphere(double u1, double u2);
GLOBAL void ons(const Vector3& v1, Vector3& v2, Vector3& v3);
void render(Vector3 *pix, int s);
void initSDL();
void quitSDL();

#endif