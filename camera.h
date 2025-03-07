#pragma once

//#include "hittable.h"
#include "material.h"


/// <summary>
/// �����������
/// </summary>
class camera
{
public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="lookfrom">���λ��</param>
	/// <param name="lookat">��������Ŀ���</param>
	/// <param name="vup">����������</param>
	/// <param name="vfov">�ӽ�</param>
	/// <param name="aspect">�ݺ��</param>
	/// <param name="aperture">�׾�</param>
	/// <param name="focus_dist">�������</param>
	camera(vec3 lookfrom, vec3 lookat, vec3 vup,
		double vfov, double aspect, double aperture, double focus_dist)
	{
		origin = lookfrom;
		lens_radius = aperture / 2.0;

		double theta = degress_to_radians(vfov);
		double half_height = tan(theta / 2);
		double half_width = aspect * half_height;

		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);

		lower_left_corner = origin
			- half_width * focus_dist * u
			- half_height * focus_dist * v
			- focus_dist * w;

		horiizonal = 2 * half_width * focus_dist * u;
		vertical = 2 * half_height * focus_dist * v;
	}

	ray get_ray(double s, double t)
	{
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		return ray(origin + offset, lower_left_corner + s * horiizonal + t * vertical - origin - offset);
	}

public:
	vec3 origin;//���ԭ��
	vec3 lower_left_corner;
	vec3 horiizonal;
	vec3 vertical;
	vec3 u;
	vec3 v;
	vec3 w;
	double lens_radius;
};