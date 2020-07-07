#ifndef DATA_HPP
#define DATA_HPP

#include "Vector3.hpp"

#define DEVICE  __host__ __device__

class 	Data {
public:
	int type;
	Vector3 clr;
	double cost;
	Vector3 emission;

	DEVICE Data(int t=0, Vector3 cl=Vector3(0), double co=0, Vector3 em=Vector3(0)) {type = t; clr = cl; cost = co, emission = em;}
};

#endif