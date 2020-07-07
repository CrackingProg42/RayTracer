#ifndef PLANE_HPP
#define PLANE_HPP

#define DEVICE  __host__ __device__

#include "Vector3.hpp"
#include "Object.hpp"

#define eps 1e-6

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

#endif