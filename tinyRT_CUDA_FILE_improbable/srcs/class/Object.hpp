#ifndef OBJECT_HPP
#define OBJECT_HPP

#define DEVICE  __host__ __device__

#include "Vector3.hpp"
#include "Ray.hpp"

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

#endif