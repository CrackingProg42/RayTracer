#ifndef RAY_HPP
#define RAY_HPP

#define DEVICE  __host__ __device__

#include "Vector3.hpp"

// Rays have origin and direction.
// The direction Vector3 should always be normalized.
class Ray {
public:
    Vector3 o, d;
    DEVICE Ray(Vector3 o0 = Vector3(), Vector3 d0 = Vector3()) : o(o0), d(d0) {}
};

#endif