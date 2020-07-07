
#include "tinyRt.hpp"

// Input is the pixel offset, output is the appropriate coordinate
// on the image plane
__device__
Vector3 camCastRay(const double x, const double y) {
	double w = W;
	double h = H;
	float fovx = PI / 4;
	float fovy = (h / w) * fovx;
	return Vector3(((2 * x - w) / w) * tan(fovx), -((2 * y - h) / h) * tan(fovy), -1.0);
}

// Uniform sampling on a hemisphere to produce outgoing ray directions
__device__
void hemisphere(double u1, double u2, Vector3 &vec) {
	const double r = sqrt(1.0 - u1*u1);
	const double phi = 2 * PI * u2;
	vec = Vector3(cos(phi)*r, sin(phi)*r, u1);
}

// given v1, set v2 and v3 so they form an orthonormal system
// (we assume v1 is already normalized)
__device__
void ons(const Vector3& v1, Vector3& v2, Vector3& v3) {
	if (std::abs(v1.x) > std::abs(v1.y)) {
		// project to the y = 0 plane and construct a normalized orthogonal vector in this plane
		float invLen = 1.f / sqrtf(v1.x * v1.x + v1.z * v1.z);
		v2 = Vector3(-v1.z * invLen, 0.0f, v1.x * invLen);
	} else {
		// project to the x = 0 plane and construct a normalized orthogonal vector in this plane
		float invLen = 1.0f / sqrtf(v1.y * v1.y + v1.z * v1.z);
		v2 = Vector3(0.0f, v1.z * invLen, -v1.y * invLen);
	}
	v3 = v1 % v2;
}