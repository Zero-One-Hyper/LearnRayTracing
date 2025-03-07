#pragma once
//#include "rtweekend.h"
//struct hit_record;
//#include "hittable.h"

/// <summary>
/// 菲涅尔
/// </summary>
/// <param name="cosine"></param>
/// <param name="ref_idx"></param>
/// <returns></returns>
double schlick(double cosine, double ref_idx);

class material
{
public :
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material
{
public:
	lambertian(const vec3& a) : albedo(a) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) 
		const override {
		vec3 scatter_direction = rec.normal + random_unit_vector();
		scattered = ray(rec.p, scatter_direction);
		attenuation = albedo;
		return true;
	}

public:
	vec3 albedo;
};

class metal : public material
{
public:
	metal(const vec3& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)
		const override {
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);//散射光线与法线 若散射光线指向内部，则认为光线被吸收
	}

public:
	vec3 albedo;
	double fuzz;//模糊度 相当于 粗糙度
};

class dielectric : public material
{
	//只会发生折射的绝缘体材质
public:
	dielectric(double ri) : ref_idx(ri)	{}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)
		const override {
		attenuation = vec3(1.0, 1.0, 1.0);
		double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);

		vec3 unit_direction = unit_vector(r_in.direction());
		double cos_theta = ffmin(dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
		if (etai_over_etat * sin_theta > 1.0)
		{
			//一定发生反射
			vec3 reflected = reflect(unit_direction, rec.normal);
			scattered = ray(rec.p, reflected);
			return true;
		}
		//折射
		double reflect_prob = schlick(cos_theta, etai_over_etat);
		if (random_double() < reflect_prob)
		{
			//菲涅尔
			vec3 reflected = reflect(unit_direction, rec.normal);
			scattered = ray(rec.p, reflected);
			return true;
		}
		vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
		scattered = ray(rec.p, refracted);
		return true;
	}

	double ref_idx;//折射率
};

double schlick(double cosine, double ref_idx)
{
	//菲涅尔
	double r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}