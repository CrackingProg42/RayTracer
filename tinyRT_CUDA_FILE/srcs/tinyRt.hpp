

#ifndef TINYRT_HPP
#define TINYRT_HPP

#include <cstdio>
#include <cmath>
#include <random>
#include <deque>
#include <map>
#include <time.h>
#include <iostream>
#include "class/Data.hpp"
#include "class/Intersection.hpp"
#include "class/Object.hpp"
#include "class/Plane.hpp"
#include "class/Ray.hpp"
#include "class/Scene.hpp"
#include "class/Sphere.hpp"
#include "class/Vector3.hpp"


#define DEVICE  __host__ __device__
using namespace std;
#define RND2(state) (float)curand_uniform(&state)
#define RND(state) (2.0*RND2(state))-1.0

#define inf 1e9
#define eps 1e-6

#define PI 3.1415926536
#define W 800
#define H 800
#define BLOCK_SIZE 5

__device__
Vector3 camCastRay(const double x, const double y);
__device__
Vector3 hemisphere(double u1, double u2);
__device__
void ons(const Vector3& v1, Vector3& v2, Vector3& v3);
void render(Vector3 *pix, int s);
void initSDL();
void quitSDL();

#endif