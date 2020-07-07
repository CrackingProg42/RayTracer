#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Bounding_box.hpp"

#define eps 1e-6

class Sphere : public Object {
public:
	Object **nodes;
	Vector3 c;
	double r2;
	int size;
    Bounding_box *box;

	DEVICE Sphere(double r_ = 0, Vector3 c_ = 0, Object **lst = nullptr, int lst_size = 0, Bounding_box *bb = nullptr) : c(c_), r2(r_*r_), nodes(lst), size(lst_size), box(bb) {}
	DEVICE virtual Intersection intersect(const Ray& ray) const {
		Vector3 m = ray.o - c;
		double b = (m * 2).dot(ray.d);
		double c_ = m.dot(m) - r2;
		double disc = b*b - 4 * c_;
		if (disc < 0) return Intersection();
		else disc = sqrt(disc);
		double sol1 = -b + disc;
		double sol2 = -b - disc;
		return (sol2 > eps) ? Intersection(sol2 / 2, (Object*)this) : ((sol1 > eps) ? Intersection(sol1 / 2, (Object*)this) : Intersection());
	}

	DEVICE virtual Vector3 normal(const Vector3& p0) const {
		return (p0 - c).norm();
	}
};

#endif