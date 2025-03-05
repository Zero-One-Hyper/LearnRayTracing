#pragma once
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

#include "ray.h"
#include "vec3.h"

//常数及常用定义

using std::shared_ptr;
using std::make_shared;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265358;

const double degress_to_radians(double degress)
{
	return degress * pi / 180;
}

inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a <= b ? b : a; }
