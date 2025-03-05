#pragma once

#include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;	//是指向一些已分配内存的类型的指针，每当你将它的值赋值给另一个智能指针时, 物体的引用计数器就会+1。
						//当智能指针离开它所在的生存范围(例如代码块或者函数外), 物体的引用计数器就会-1。一旦引用计数器为0, 即没有任何智能指针指向该物体时, 该物体就会被销毁
using std::make_shared;//为指定的类型分配一段内存, 使用你指定的构造函数与参数来创建这个类, 并返回一个智能指针shared_ptr<thing>

/// <summary>
/// 存放物体的列表
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