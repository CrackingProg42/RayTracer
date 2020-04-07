
#include "tinyRt.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

void trace(Ray &ray, const Scene& scene, int depth, Vector3& clr, pl& params) {
	// Russian roulette: starting at depth 5, each recursive step will stop with a probability of 0.1
	double rrFactor = 1.0;
	if (depth >= 5) {
		const double rrStopProbability = 0.1;
		if (RND2 <= rrStopProbability) {
			return;
		}
		rrFactor = 1.0 / (1.0 - rrStopProbability);
	}

	Intersection intersection = scene.intersect(ray);
	if (!intersection) return;

	// Travel the ray to the hit point where the closest object lies and compute the surface normal there.
	Vector3 hp = ray.o + ray.d * intersection.t;
	Vector3 N = intersection.obj->normal(hp);
	ray.o = hp;

	// Add the emission, the L_e(x,w) part of the rendering equation, but scale it with the Russian Roulette
	// probability weight.
	const double emission = intersection.obj->emission;
	clr = clr + Vector3(emission, emission, emission) * rrFactor;

	// Diffuse BRDF - choose an outgoing direction with hemisphere sampling.
	if (intersection.obj->type == 1) {
		Vector3 rotX, rotY;
		ons(N, rotX, rotY);
		Vector3 sampledDir = hemisphere(RND2, RND2);
		Vector3 rotatedDir;
		rotatedDir.x = Vector3(rotX.x, rotY.x, N.x).dot(sampledDir);
		rotatedDir.y = Vector3(rotX.y, rotY.y, N.y).dot(sampledDir);
		rotatedDir.z = Vector3(rotX.z, rotY.z, N.z).dot(sampledDir);
		ray.d = rotatedDir;	// already normalized
		double cost = ray.d.dot(N);
		Vector3 tmp;
		trace(ray, scene, depth + 1, tmp, params);
		clr = clr + (tmp * intersection.obj->color) * cost * 0.1 * rrFactor;
	}

	// Specular BRDF - this is a singularity in the rendering equation that follows
	// delta distribution, therefore we handle this case explicitly - one incoming
	// direction -> one outgoing direction, that is, the perfect reflection direction.
	if (intersection.obj->type == 2) {
		double cost = ray.d.dot(N);
		ray.d = (ray.d - N*(cost * 2)).norm();
		Vector3 tmp = Vector3(0, 0, 0);
		trace(ray, scene, depth + 1, tmp, params);
		clr = clr + tmp * rrFactor;
	}

	// Glass/refractive BRDF - we use the vector version of Snell's law and Fresnel's law
	// to compute the outgoing reflection and refraction directions and probability weights.
	if (intersection.obj->type == 3) {
		double n = params["refr_index"];
		double R0 = (1.0 - n) / (1.0 + n);
		R0 = R0*R0;
		if (N.dot(ray.d) > 0) { // we're inside the medium
			N = N*-1;
			n = 1 / n;
		}
		n = 1 / n;
		double cost1 = (N.dot(ray.d))*-1; // cosine of theta_1
		double cost2 = 1.0 - n*n*(1.0 - cost1*cost1); // cosine of theta_2
		double Rprob = R0 + (1.0 - R0) * pow(1.0 - cost1, 5.0); // Schlick-approximation
		if (cost2 > 0 && RND2 > Rprob) { // refraction direction
			ray.d = ((ray.d*n) + (N*(n*cost1 - sqrt(cost2)))).norm();
		} else { // reflection direction
			ray.d = (ray.d + N*(cost1 * 2)).norm();
		}
		Vector3 tmp;
		trace(ray, scene, depth + 1, tmp, params);
		clr = clr + tmp * 1.15 * rrFactor;
	}
}

void calc_render(pl params, Scene scene, Vector3 ***pix) {

	for (int col = 0; col < W; col++) {
		for (int row = 0; row < H; row++) {
			Vector3 color;
			Ray ray;
			ray.o = (Vector3(0, 0, 0)); // rays start out from here
			Vector3 cam = camCastRay(col, row); // construct image plane coordinates
			cam.x = cam.x + RND / 700; // anti-aliasing for free
			cam.y = cam.y + RND / 700;
			ray.d = (cam - ray.o).norm(); // point from the origin to the camera plane
			trace(ray, scene, 0, color, params);
			(*pix)[col][row] = (*pix)[col][row] + color;
		}
	}
}

void render(SDL_Renderer **renderer, Vector3 **pix, int s) {
	for (int col = 0; col < W*2; col = col + 2) {
		for (int row = 0; row < H*2; row = row + 2) {
			SDL_SetRenderDrawColor(*renderer, std::min((int)(pix[col / 2][row / 2].x / (s + 1)), 255), std::min((int)(pix[col / 2][row / 2].y / (s + 1)), 255), std::min((int)(pix[col / 2][row / 2].z / (s + 1)), 255), 255);
			SDL_RenderDrawPoint(*renderer, col, row);
			SDL_RenderDrawPoint(*renderer, col, row + 1);
			SDL_RenderDrawPoint(*renderer, col + 1, row);
			SDL_RenderDrawPoint(*renderer, col + 1, row + 1);
		}
	}
	SDL_RenderPresent(*renderer);
}

int main(int ac, char **av) {
	//in av : av[1] = spp, av[2] = refraction_index
	SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

	int spp;
	float refr_ind;
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

	Scene scene;
	auto add = [&scene](Object* s, Vector3 cl, double emission, int type) {
		s->setMat(cl, emission, type);
		scene.add(s);
	};

	// Radius, position, color, emission, type (1=diff, 2=spec, 3=refr) for spheres
	add(new Sphere(1.05, Vector3(-0.75, -1.45, -4.4)), Vector3(4, 8, 4), 0, 2); // Middle sphere
	add(new Sphere(0.5, Vector3(2.0, -2.05, -3.7)), Vector3(10, 10, 1), 0, 3); // Right sphere
	add(new Sphere(0.6, Vector3(-1.75, -1.95, -3.1)), Vector3(4, 4, 12), 0, 1); // Left sphere
	// Position, normal, color, emission, type for planes
	add(new Plane(2.5, Vector3(0, 1, 0)), Vector3(6, 6, 6), 0, 1); // Bottom plane
	add(new Plane(5.5, Vector3(0, 0, 1)), Vector3(6, 6, 6), 0, 1); // Back plane
	add(new Plane(2.75, Vector3(1, 0, 0)), Vector3(10, 2, 2), 0, 1); // Left plane
	add(new Plane(2.75, Vector3(-1, 0, 0)), Vector3(2, 10, 2), 0, 1); // Right plane
	add(new Plane(3.0, Vector3(0, -1, 0)), Vector3(6, 6, 6), 0, 1); // Ceiling plane
	add(new Plane(0.5, Vector3(0, 0, -1)), Vector3(6, 6, 6), 0, 1); // Front plane
	add(new Sphere(0.5, Vector3(0, 1.9, -3)), Vector3(0, 0, 0), 1000, 1); // Light

	params["refr_index"] = refr_ind;
	params["spp"] = spp; // samples per pixel

	Vector3 **pix = new Vector3*[W];
	for (int i = 0; i < W; i++) {
		pix[i] = new Vector3[H];
	}
	
	SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(W*2, H*2, 0, &window, &renderer);

	for (int s = 0; s < spp; s++) {
		calc_render(params, scene, &pix);
		render(&renderer, pix, s);
	}

	while (1) {
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
	}
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}