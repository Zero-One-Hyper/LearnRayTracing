#pragma once
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <cstdlib>


//常数及常用定义

using std::shared_ptr;//是指向一些已分配内存的类型的指针，每当你将它的值赋值给另一个智能指针时, 物体的引用计数器就会+1。
						//当智能指针离开它所在的生存范围(例如代码块或者函数外), 物体的引用计数器就会-1。一旦引用计数器为0, 即没有任何智能指针指向该物体时, 该物体就会被销毁
using std::make_shared;//为指定的类型分配一段内存, 使用你指定的构造函数与参数来创建这个类, 并返回一个智能指针shared_ptr<thing>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265358;

const double degress_to_radians(double degress)
{
	return degress * pi / 180;
}

//最大最小
inline double ffmin(double a, double b) { return a <= b ? a : b; }
inline double ffmax(double a, double b) { return a <= b ? b : a; }

//随机数
inline double random_double() { return rand() / (RAND_MAX + 1.0); }//取值范围[0, 1)
inline double random_double(double min, double max) { return min + (max - min) * random_double(); }

//钳制
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

#include "ray.h"
#include "vec3.h"
