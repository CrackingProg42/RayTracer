
#include "tinyRt.hpp"

void trace(Data *clrlist, Ray &ray, Scene **scene, Vector3& clr, float refr_ind, int bounce_max) {
	// Russian roulette: starting at depth 5, each recursive step will stop with a probability of 0.1
	Data dt;
	Vector3 tmp;
	Intersection intersection;
	Vector3 hp;
	Vector3 N;
	Vector3 rotX, rotY;
	Vector3 sampledDir;
	Vector3 rotatedDir;

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
			if (RND2 <= rrStopProbability) {
				break;
			}
			rrFactor = 1.0 / (1.0 - rrStopProbability);
		}

		intersection = (*scene)->intersect(ray);
		
		if (!intersection) break;

		// Travel the ray to the hit point where the closest object lies and compute the surface normal there.
		hp = ray.o + ray.d * intersection.t;
		N = intersection.obj->normal(hp);
		ray.o = hp;
		// Add the emission, the L_e(x,w) part of the rendering equation, but scale it with the Russian Roulette
		// probability weight.
		const double emission = intersection.obj->emission;
		tmp = Vector3(emission, emission, emission) * rrFactor;

		// Diffuse BRDF - choose an outgoing direction with hemisphere sampling.
		if (intersection.obj->type == 1) {
			ons(N, rotX, rotY);
			sampledDir = hemisphere(RND2, RND2);
			rotatedDir.x = Vector3(rotX.x, rotY.x, N.x).dot(sampledDir);
			rotatedDir.y = Vector3(rotX.y, rotY.y, N.y).dot(sampledDir);
			rotatedDir.z = Vector3(rotX.z, rotY.z, N.z).dot(sampledDir);
			ray.d = rotatedDir;	// already normalized
			cost = ray.d.dot(N);
			dt = Data(1, intersection.obj->color, cost, tmp);
		}

		// Specular BRDF - this is a singularity in the rendering equation that follows
		// delta distribution, therefore we handle this case explicitly - one incoming
		// direction -> one outgoing direction, that is, the perfect reflection direction.
		if (intersection.obj->type == 2) {
			cost = ray.d.dot(N);
			ray.d = (ray.d - N*(cost * 2)).norm();
			dt = Data(2, intersection.obj->color, cost, tmp);
		}

		// Glass/refractive BRDF - we use the vector version of Snell's law and Fresnel's law
		// to compute the outgoing reflection and refraction directions and probability weights.
		if (intersection.obj->type == 3) {
			n = refr_ind;
			R0 = (1.0 - n) / (1.0 + n);
			R0 = R0*R0;
			if (N.dot(ray.d) > 0) { // we're inside the medium
				N = N*-1;
				n = 1 / n;
			}
			n = 1 / n;
			cost1 = (N.dot(ray.d))*-1; // cosine of theta_1
			cost2 = 1.0 - n*n*(1.0 - cost1*cost1); // cosine of theta_2
			Rprob = R0 + (1.0 - R0) * pow(1.0 - cost1, 5.0); // Schlick-approximation
			if (cost2 > 0 && RND2 > Rprob) { // refraction direction
				ray.d = ((ray.d*n) + (N*(n*cost1 - sqrt(cost2)))).norm();
			} else { // reflection direction
				ray.d = (ray.d + N*(cost1 * 2)).norm();
			}
			dt = Data(3, intersection.obj->color, cost1, tmp);
		}

		clrlist[bounce_max - depth - 1] = dt;
	}
	for (int i = 0; i < bounce_max ; i++) {
		if (clrlist[i].type == 1) {
			clr = clrlist[i].emission + (clr * clrlist[i].clr) * clrlist[i].cost * 0.1 * rrFactor;
		}
		if (clrlist[i].type == 2) {
			clr = clrlist[i].emission + clr * rrFactor;
		}
		if (clrlist[i].type == 3) {
			clr = clrlist[i].emission + clr * 1.15 * rrFactor;
		}
	}
}

void calc_render(int bounce_max, Data *clrlist, float refr_ind, int spp, Scene **scene, Vector3 *pix) {
	for (int col = 0; col < W; col++) {
		for (int row = 0; row < H; row++) {
			int pixel_index = col*W + row;
			Vector3 color = Vector3(0, 0, 0);
			Ray ray;
			ray.o = (Vector3(0, 0, 0)); // rays start out from here
			Vector3 cam = camCastRay(col, row); // construct image plane coordinates
			cam.x = cam.x + RND / 700; // anti-aliasing for free
			cam.y = cam.y + RND / 700;
			ray.d = (cam - ray.o).norm(); // point from the origin to the camera plane
			trace(clrlist, ray, scene, color, refr_ind, bounce_max);
			pix[pixel_index] = pix[pixel_index] + color;
		}
	}
}

void create_world(Object **d_list, int size, Scene **d_scene) {
	
	*(d_list)   = new Sphere(1.05, Vector3(-0.75, -1.45, -4.4));
	(*(d_list))->setMat(Vector3(4, 8, 4), 0, 2);

	*(d_list + 1)  = new Sphere(0.5, Vector3(2.0, -2.05, -3.7));
	(*(d_list + 1))->setMat(Vector3(10, 10, 1), 0, 3);
	
	*(d_list + 2)  = new Sphere(0.6, Vector3(-1.75, -1.95, -3.1));
	(*(d_list + 2))->setMat(Vector3(4, 4, 12), 0, 1);

	*(d_list + 3)   = new Plane(2.5, Vector3(0, 1, 0));
	(*(d_list + 3))->setMat(Vector3(6, 6, 6), 0, 1);

	*(d_list + 4)   = new Plane(5.5, Vector3(0, 0, 1));
	(*(d_list + 4))->setMat(Vector3(6, 6, 6), 0, 1);

	*(d_list + 5)   = new Plane(2.75, Vector3(1, 0, 0));
	(*(d_list + 5))->setMat(Vector3(10, 2, 2), 0, 1);

	*(d_list + 6)   = new Plane(2.75, Vector3(-1, 0, 0));
	(*(d_list + 6))->setMat(Vector3(2, 10, 2), 0, 1);

	*(d_list + 7)   = new Plane(3.0, Vector3(0, -1, 0));
	(*(d_list + 7))->setMat(Vector3(6, 6, 6), 0, 1);

	*(d_list + 8)   = new Plane(0.5, Vector3(0, 0, -1));
	(*(d_list + 8))->setMat(Vector3(6, 6, 6), 0, 1);

	*(d_list + 9)   = new Sphere(0.5, Vector3(0, 1.9, -3));
	(*(d_list + 9))->setMat(Vector3(0, 0, 0), 5000, 1);
	*d_scene = new Scene(d_list, size);
}

int main(int ac, char **av) {
	//in av : av[1] = spp, av[2] = refraction_index
	int bounce_max = 20;
	int tx = 8;
	int ty = 8;
	int spp;
	float refr_ind;
	int obj_num = 10;

	if (ac >= 2)
		spp = std::atoi(av[1]);
	else
		spp = 1000;

	if (ac >= 3)
		refr_ind = std::atof(av[2]);
	else
		refr_ind = 1.9;
	
	srand(time(NULL));
	pl params;

	Object** list;
	list = (Object**)malloc(sizeof(Object*) * obj_num);

	Scene** scene;
	scene = (Scene**)malloc(sizeof(Scene*));

	create_world(list, obj_num, scene);

	Vector3 *pix = (Vector3 *)malloc(H*W*sizeof(Vector3));

	initSDL();
	for (int s = 0; s < spp; s++) {
		Data *clrlist = (Data *)malloc(sizeof(Data) * bounce_max);
		calc_render(bounce_max, clrlist, refr_ind, spp, scene, pix);
		render(pix, s);
		free(clrlist);
		break;
	}
	quitSDL();
	return 0;
}