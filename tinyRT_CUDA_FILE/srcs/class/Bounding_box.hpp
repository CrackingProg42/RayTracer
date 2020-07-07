#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

#include "Vector3.hpp"
#include "Ray.hpp"

#define DEVICE  __host__ __device__

#define inf 1e9

class Bounding_box {
public:
    DEVICE Bounding_box() {}
    DEVICE Bounding_box(const Vector3 &a, const Vector3 &b) { _min = a; _max = b;}

    DEVICE Vector3 min() const {return _min; }
    DEVICE Vector3 max() const {return _max; }

    DEVICE bool intersect(const Ray& r) const {
        return 1;
        double t = inf;
        double tmax = inf;
        double tmp;
        Vector3 invD = Vector3(1 / r.d.x, 1 / r.d.y, 1 / r.d.z);
        Vector3 t0 = (min() - r.o) * invD;
        Vector3 t1 = (max() - r.o) * invD;
        if (invD.x < 0.0f) {
            tmp = t0.x;
            t0.x = t1.x;
            t1.x = tmp;
        }
        if (invD.y < 0.0f) {
            tmp = t0.y;
            t0.y = t1.y;
            t1.y = tmp;
        }
        if (invD.z < 0.0f) {
            tmp = t0.z;
            t0.z = t1.z;
            t1.z = tmp;
        }
        t = t0.x > t ? t0.x : t;
        tmax = t1.x < tmax ? t1.x : tmax;
        if (tmax <= t)
            return 0;
        t = t0.y > t ? t0.y : t;
        tmax = t1.y < tmax ? t1.y : tmax;
        if (tmax <= t)
            return 0;
        t = t0.z > t ? t0.z : t;
        tmax = t1.z < tmax ? t1.z : tmax;
        if (tmax <= t)
            return 0;
        return 1;
    }

    Vector3 _min;
    Vector3 _max;
};

/*
Bounding_box surrounding_box(Bounding_box box0, Bounding_box box1) {
    Vector3 small(  fminf(box0.min().x, box1.min().x),
                    fminf(box0.min().y, box1.min().y),
                    fminf(box0.min().z, box1.min().z) );
    Vector3 big(    fmaxf(box0.max().x, box1.max().x),
                    fmaxf(box0.max().y, box1.max().y),
                    fmaxf(box0.max().z, box1.max().z) );
    return (Bounding_box(small, big));
}*/

#endif