#pragma once
//#include "rtweekend.h"
//#include "ray.h"


//hittable��material�ȶ��壬������Ҫ������material ����Camera��include material
class material;

/// <summary>
/// ������ײ��¼
/// </summary>
struct hit_record
{
	vec3 p;//��ײ��
	vec3 normal; //��ײ��ķ���
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
/// �κ��������ཻ�Ķ������̳д˳�����
/// </summary>
class hittable
{
public :
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};