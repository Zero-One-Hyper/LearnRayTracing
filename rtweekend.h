#pragma once
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <cstdlib>

#include "ray.h"
#include "vec3.h"

//���������ö���

using std::shared_ptr;
using std::make_shared;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265358;

const double degress_to_radians(double degress)
{
	return degress * pi / 180;
}

//�����С
inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a <= b ? b : a; }

//�����
inline double random_double() { return rand() / (RAND_MAX + 1.0); }//ȡֵ��Χ[0, 1)
inline double random_double(double min, double max) { return min + (max - min) * random_double(); }

//ǯ��
inline double clamp(double x, double min, double max)
{
	if (x < min)
	{
		return min;
	}
	if (x > max)
	{
		return max;
	}
	return x;
}
