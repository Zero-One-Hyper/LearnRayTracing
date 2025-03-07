#pragma once
//#include "rtweekend.h"
#include <iostream>

class vec3
{
public:
	vec3() : e{ 0, 0, 0 } {}
	vec3(double e1, double e2, double e3) : e{ e1, e2, e3 } {}
	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }
	
	vec3 operator-() const 
	{
		return vec3(-e[0], -e[1], -e[2]);
	}
	double operator[](int i) const
	{
		return e[i];
	}
	double& operator[](int i)
	{
		return e[i];
	}

	vec3& operator+=(const vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3& operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(const double t)
	{
		return *this *= 1 / t;
	}

	double length() const
	{
		return sqrt(length_squared());
	}

	double length_squared() const
	{
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	//д��ɫ��������ݴ��������ܱ߶�β���������
	void write_color(std::ostream& out, int sample_per_pixel, int pixelindex, double* colorarray)
	{ 
		double scale = 1.0 / sample_per_pixel;//�����˶��ٸ����أ�������ص���ɫռ�����ص� 1.0 / sample_per_pixel
		//gamma���� ����
		double r = sqrt(scale * e[0]);
		double g = sqrt(scale * e[1]);
		double b = sqrt(scale * e[2]);

		colorarray[pixelindex] = r;
		colorarray[pixelindex + 1] = g;// (256 * clamp(g, 0.0, 0.999));
		colorarray[pixelindex + 2] = b;// (256 * clamp(b, 0.0, 0.999));

		//out << static_cast<int>(pixelindex) << std::endl;

		//��vector3(0-1)ת���������ɫ(0-256)
		//out << static_cast<int>(256 * clamp(colorarray[pixelindex], 0.0, 0.999)) << ' '
		//	<< static_cast<int>(256 * clamp(colorarray[pixelindex + 1], 0.0, 0.999)) << ' '
		//	<< static_cast<int>(256 * clamp(colorarray[pixelindex + 2], 0.0, 0.999)) << '\n';
	}

	inline static vec3 random()
	{
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max)
	{
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}
public:
	double e[3];
};

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
	return out << v.e[0] << ' ' << v.e[1] << v.e[2];
}
inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
inline vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
inline vec3 operator*(double t, const vec3& v)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}
inline vec3 operator*(const vec3& v, double t)
{
	return t * v;
}
inline vec3 operator/(vec3 v, double t)
{
	return (1 / t) * v;
}
inline double dot(const vec3& u, const vec3& v)
{
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}
inline vec3 cross(vec3& u, vec3& v)
{
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
inline vec3 unit_vector(vec3 v)
{
	//��һ��
	return v / v.length();
}
inline vec3 reflect(const vec3& v, const vec3& n)
{
	//����
	return v - 2 * dot(v, n) * n;
}
inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat)
{
	//����
	double cos_theta = dot(-uv, n);
	vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * n);
	vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
	return r_out_parallel + r_out_perp;
}

/// <summary>
/// �ڵ�λԲ�����������
/// </summary>
/// <returns></returns>
inline vec3 random_in_unit_sphere()
{
	while (true)
	{
		vec3 p = vec3::random(1, -1);
		//���һ���� �ж�����㵽��0��0��0���ľ����Ƿ�С��1
		if (p.length_squared() >= 1)
		{
			continue;
		}
		return p;
	}
}

/// <summary>
/// ʹ�ü����귽ʽ �ڵ�λԲ��ȡ����㣬Ȼ��λ��
/// </summary>
/// <returns></returns>
inline vec3 random_unit_vector()
{
	double a = random_double(0, 2 * pi);
	double z = random_double(-1, 1);
	double r = sqrt(1 - z * z);
	return vec3(r * cos(a), r * sin(a), z);
}

/// <summary>
/// ѡ��һ����λԲ�ڵ�����㣬Ȼ���ж�������Ƿ��ڷ��ߵİ����ڣ�������򷵻�����㣬���򷵻������ķ�����
/// </summary>
/// <param name="normal"></param>
/// <returns></returns>
inline vec3 random_in_hemisphere(const vec3& normal)
{
	vec3 in_unit_shpere = random_in_unit_sphere();
	if (dot(in_unit_shpere, normal) > 0.0)
	{
		return in_unit_shpere;
	}
	else
	{
		return -in_unit_shpere;
	}
}
/// <summary>
/// ��Բ������������ߣ��������������
/// </summary>
/// <returns></returns>
inline vec3 random_in_unit_disk()
{
	while (true)
	{
		vec3 p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.length_squared() >= 1)
		{
			continue;
		}
		return p;
	}
}