#pragma once
//#include "rtweekend.h"
//#include "ray.h"


//hittable比material先定义，这里需要先声明material 后面Camera会include material
class material;

/// <summary>
/// 射线碰撞记录
/// </summary>
struct hit_record
{
	vec3 p;//碰撞点
	vec3 normal; //碰撞点的法线
	shared_ptr<material> mat_ptr;
	double t;
	bool front_face;

	inline void set_face_normal(const ray& r, const vec3& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

/// <summary>
/// 任何与射线相交的东西都继承此抽象类
/// </summary>
class hittable
{
public :
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};