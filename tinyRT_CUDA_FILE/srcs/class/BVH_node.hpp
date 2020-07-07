#ifndef BVH_NODE_HPP
#define BVH_NODE_HPP

#define DEVICE  __host__ __device__
#include "Bounding_box.hpp"
#include "Object.hpp"

class BVH {
public:
    Object **nodes;
    int size;
    Bounding_box box;

    DEVICE BVH() {}
    DEVICE BVH(Object **lst, int lst_size, Bounding_box bb) : nodes(lst), size(lst_size), box(bb) {}
    DEVICE Intersection intersect(const Ray& ray) const {
        Intersection closestIntersection;
        if (box.intersect(ray)) {
            for (int i = 0; i < size; i++) {
                Intersection inter = nodes[i]->intersect(ray);
                if (inter && inter.t < closestIntersection.t) {
                    closestIntersection = inter;
                }
            }
        }
        return closestIntersection;
    }
};

#endif