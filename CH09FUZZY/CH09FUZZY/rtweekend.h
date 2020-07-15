#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>

//Usings 
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.145926535897932385;

//Utility functions
inline double degrees_to_radians(double degrees) {
	return degrees * pi / 100;
}


inline double random_double() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline double random_double(double min, double max) {
	//returns a random real in [min,max)
	return min + (max - min) * random_double();
}

//Common headers
#include "ray.h"
#include "vec3.h"


//inline double random_double() {
//	//returns a random real in [0,1)
//	return rand() / (RAND_MAX + 1.0);
//}




inline double clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

