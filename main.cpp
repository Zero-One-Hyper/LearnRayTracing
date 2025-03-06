#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include <iostream>

//��֤����ͷ�ļ�ֻincludeһ��

double hit_sphere(const vec3& center, double radius, const ray& r);
vec3 ray_color(const ray& r, const hittable& world, int depth);
hittable_list random_scene();//�������

int main()
{
    const int image_width = 200;
    const int image_height = 100;
    const int sample_per_pixel = 100;//����ݴ���ÿ���������ܱ߲������ٴ�
    const int max_depth = 50;//��������
    const double r = cos(pi / 4);
    const vec3 lookfrom = vec3(-2, 2, 1);
    const vec3 lookat = vec3(0, 0, -1);
	const vec3 vup = vec3(0, 1, 0);
    const double fov = 90;
    const double aspect_ratio = double(image_width) / image_height;
    const double dist_to_focus = (lookfrom - lookat).length();
    const double aperture = 2.0;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    //vec3 lower_left_corner{ 1.0, -1.0, -1.0 };
    //vec3 horiizonal{ 4.0, 0.0, 0.0 };
    //vec3 vertical{ 0.0, 2.0, 0.0 };
    //vec3 origin{0.0, 0.0, 0.0};

    hittable_list world = random_scene();
    world.add(make_shared<sphere>(vec3(0, 0, -1), 0.5, make_shared<lambertian>(vec3(0.7, 0.3, 0.3))));//sphereҪ public�̳�hittable
    world.add(make_shared<sphere>(vec3(0, -100.5, -1), 100, make_shared<lambertian>(vec3(0.8, 0.8, 0.0))));

	world.add(make_shared<sphere>(vec3(1, 0, -1), 0.5, make_shared<metal>(vec3(0.8, 0.6, 0.2), 0.9)));
    world.add(make_shared<sphere>(vec3(-1, 0, -1), 0.5, make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(vec3(-1, 0, -1), -0.35, make_shared<dielectric>(1.5)));//�뾶ȡ�� �õ��������ڵ�����

    camera cam(lookfrom, lookat, vup, fov, aspect_ratio,dist_to_focus, aperture);

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            //�Ե�ǰ���ؽ�����ɫ
            vec3 color;
            //����ݶ�β���
            for (int s = 0; s < sample_per_pixel; s++)
            {
                double u = (i + random_double()) / image_width;
                double v = (j + random_double()) / image_height;
                ray r = cam.get_ray(u, v);
                color += ray_color(r, world, max_depth);
            }
            color.write_color(std::cout, sample_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
    //return 0;
}

double hit_sphere(const vec3& center, double radius, const ray& r)
{
    //���������Ƿ��������
    vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    //double b = 2.0 * dot(oc, r.direction());//��Ϊ
    //double c = dot(oc, oc) - radius * radius;
    //double discriminant = b * b - 4 * a * c;
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - radius * radius;
    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
    {
        return -1;
    }
    else
    {
        //return (-b - sqrt(discriminant)) / (2.0 * a);
        return (-half_b - sqrt(discriminant)) / a;
    }
}

vec3 ray_color(const ray& r, const hittable& world, int depth)
{
    //��ֹ���޷���
    if (depth <= 0)
    {
        return vec3(0, 0, 0);
    }
    /*
    double t = hit_sphere(vec3(0, 0, -1), 0.5, r);
    if (t > 0, 0)
    {
        //���߻�������
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * vec3(N.x() + 1, N.y + 1, N.z() + 1);
    }
    */
    hit_record rec;
	if (world.hit(r, 0.0001, infinity, rec))//�����ཻ 0.0001��ֹ���ཻ
    {
        ray scattered;
        vec3 attenuaion;
        //return 0.5 * (rec.normal + vec3(1, 1, 1));//��ʱ�÷�����Ϊ��ɫ���
        
        //�ڻ��е��⣨���е�p+���淨��normal�� Ѱ��һ������� ������������㷴�����ߵķ���
        //vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        //vec3 target = rec.p + rec.normal + random_unit_vector();//��λԲ�ڵ� normalize
        //vec3 target = rec.p + random_in_hemisphere(rec.normal);//�����е����һ������ ���ڵĹ���׷�������д󲿷�ʹ�õĶ����������:
        //return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
        //���ռ����Ϊ���䵽λ�õĲ��ʼ���
		if (rec.mat_ptr->scatter(r, rec, attenuaion, scattered))
		{
			return attenuaion * ray_color(scattered, world, depth - 1);
		}
        return vec3(0, 0, 0);
    }
    //��պ���� ��y�����lerp��ɫ
    vec3 unit_direction = unit_vector(r.dir);
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

hittable_list random_scene()
{
    hittable_list world;

    world.add(make_shared<sphere>(vec3(0, -1000, 0), 1000, make_shared<lambertian>(vec3(0.5, 0.5, 0.5))));
    return world;
    int i = 1;
    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            double choose_mat = random_double();
            vec3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
            if ((center - vec3(4, 0.2, 0)).length() > 0.9)
            {
                if (choose_mat < 0.8)
                {
                    //��ͨ������
                    vec3 albedo = vec3::random() * vec3::random();
                    world.add(make_shared<sphere>(center, 0.2, make_shared<lambertian>(albedo)));
                }
                else if (choose_mat < 0.95)
                {
                    //����
                    vec3 albedo = vec3::random(0.5, 1);
                    double fuzz = random_double(0, 0.5);
                    world.add(make_shared<sphere>(center, 0.2, make_shared<metal>(albedo, fuzz)));
                }
                else
                {
                    //����
                    world.add(make_shared<sphere>(center, 0.2, make_shared<dielectric>(1.5)));
                }
            }
        }
    }
    world.add(make_shared<sphere>(vec3(0, 1, 0), 1.0, make_shared<dielectric>(1.5)));

    world.add(make_shared<sphere>(vec3(-4, 1, 0), 1.0, make_shared<lambertian>(vec3(0.4, 0.2, 0.1))));

    world.add(make_shared<sphere>(vec3(4, 1, 0), 1.0, make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));
    return world;
}