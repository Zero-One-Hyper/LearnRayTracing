#pragma once

#include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;	//��ָ��һЩ�ѷ����ڴ�����͵�ָ�룬ÿ���㽫����ֵ��ֵ����һ������ָ��ʱ, ��������ü������ͻ�+1��
						//������ָ���뿪�����ڵ����淶Χ(����������ߺ�����), ��������ü������ͻ�-1��һ�����ü�����Ϊ0, ��û���κ�����ָ��ָ�������ʱ, ������ͻᱻ����
using std::make_shared;//Ϊָ�������ͷ���һ���ڴ�, ʹ����ָ���Ĺ��캯������������������, ������һ������ָ��shared_ptr<thing>

/// <summary>
/// ���������б�
/// </summary>
class hittable_list : public hittable
{
public:
	hittable_list();
	hittable_list(shared_ptr<hittable> object) { add(object); }

	void clear() { objects.clear(); }
	void add(shared_ptr<hittable> object) { objects.push_back(object); }

	virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec)const;

public:
	std::vector<shared_ptr<hittable>> objects;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec)const
{
	hit_record temp_rec;
	bool hit_anything = false;
	double closest_so_far = t_max;

	for (const auto& object : objects)
	{
		if (object->hit(r, t_min, t_max, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}