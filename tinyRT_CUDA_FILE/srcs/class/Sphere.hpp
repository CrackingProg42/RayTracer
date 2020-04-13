#ifndef SPHERE_HPP
#define SPHERE_HPP

#define DEVICE  __host__ __device__
#include "Vector3.hpp"

#define eps 1e-6

class Sphere : public Object {
public:
	Vector3 c;
	double r2;

	DEVICE Sphere(double r_ = 0, Vector3 c_ = 0) : c(c_), r2(r_*r_) {}
	DEVICE virtual double intersect(const Ray& ray) const {
		Vector3 m = ray.o - c;
		double b = (m * 2).dot(ray.d);
		double c_ = m.dot(m) - r2;
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

#endif