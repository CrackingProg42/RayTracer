#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#define DEVICE  __host__ __device__

#include "Object.hpp"

#define inf 1e9

class Intersection {
public:
	DEVICE Intersection() : t(inf), obj(nullptr) {}
	DEVICE Intersection(double t_, Object* obj_) : t(t_), obj(obj_) {}
	DEVICE operator bool() { return obj != nullptr; }
	double t;
	Object* obj;
};

#endif