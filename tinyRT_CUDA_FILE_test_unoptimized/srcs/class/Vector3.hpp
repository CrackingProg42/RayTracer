#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#define DEVICE  __host__ __device__

class Vector3 {
public:
    double x, y, z;
    DEVICE Vector3(double x0, double y0, double z0) : x(x0), y(y0), z(z0) {}
    DEVICE Vector3() : x(0), y(0), z(0) {}
    DEVICE Vector3(double d) : x(d), y(d), z(d) {}
    DEVICE Vector3 operator+(const Vector3 &b) const { return Vector3(x+b.x, y+b.y, z+b.z); }
    DEVICE Vector3 operator-(const Vector3 &b) const { return Vector3(x-b.x, y-b.y, z-b.z); }
    DEVICE Vector3 operator*(double b) const { return Vector3(x*b, y*b, z*b); }
    DEVICE Vector3 operator/(double b) const { return Vector3(x/b, y/b, z/b); }
    DEVICE Vector3 operator*(const Vector3 &b) const { return Vector3(x*b.x, y*b.y, z*b.z); }
    DEVICE Vector3& norm() { return *this = *this / length(); }
    DEVICE double length() { return sqrt(x*x+y*y+z*z); }
    DEVICE double dot(const Vector3 &b) const { return x*b.x+y*b.y+z*b.z; }
    DEVICE Vector3 operator%(Vector3 &b) const { return Vector3(y*b.z-z*b.y, z*b.x-x*b.z, x*b.y-y*b.x); }
};

#endif