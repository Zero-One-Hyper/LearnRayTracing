#include "rtweekend.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include <iostream>

double hit_sphere(const vec3& center, double radius, const ray& r);
vec3 ray_color(const ray& r, const hittable& world);

int main()
{
    const int image_width = 200;
    const int image_height = 100;
    const int sample_per_pixel = 100;//抗锯齿处理，每个像素向周边采样多少次

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    //vec3 lower_left_corner{ 1.0, -1.0, -1.0 };
    //vec3 horiizonal{ 4.0, 0.0, 0.0 };
    //vec3 vertical{ 0.0, 2.0, 0.0 };
    //vec3 origin{0.0, 0.0, 0.0};

    hittable_list world;
    world.add(make_shared<sphere>(vec3(0, 0, -1), 0.5));//sphere要 public继承hittable
    world.add(make_shared<sphere>(vec3(0, -100.5, -1), 100));

    camera cam;

    for (int j = image_height - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            vec3 color;
            //抗锯齿多次采样
            for (int s = 0; s < sample_per_pixel; s++)
            {
                double u = (i + random_double()) / image_width;
                double v = (j + random_double()) / image_height;
                ray r = cam.get_ray(u, v);
                color += ray_color(r, world);
            }
            color.write_color(std::cout, sample_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
    //return 0;
}

double hit_sphere(const vec3& center, double radius, const ray& r)
{
    //计算射线是否击中球体
    vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    //double b = 2.0 * dot(oc, r.direction());//简化为
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

vec3 ray_color(const ray& r, const hittable& world)
{
    /*
    double t = hit_sphere(vec3(0, 0, -1), 0.5, r);
    if (t > 0, 0)
    {
        //射线击中球体
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * vec3(N.x() + 1, N.y + 1, N.z() + 1);
    }
    */
    hit_record rec;
    if (world.hit(r, 0, infinity, rec))
    {
        //暂时用法线作为颜色输出
        return 0.5 * (rec.normal + vec3(1, 1, 1));
    }
    //天空盒填充 用y轴填充lerp蓝色
    vec3 unit_direction = unit_vector(r.dir);
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
