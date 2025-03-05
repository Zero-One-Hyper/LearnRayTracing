#pragma once

#include "rtweekend.h"

/// <summary>
/// ¼òÒ×ÉãÏñ»úÀà
/// </summary>
class camera
{
public:
	camera()
	{
		lower_left_corner = vec3(-2.0, -1.0, -1.0);
		horiizonal = vec3(4.0, 0.0, 0.0);
		vertical = vec3(0.0, 2.0, 0.0);
		origin = vec3(0.0, 0.0, 0.0);
	}

	ray get_ray(double u, double v)
	{
		return ray(origin, lower_left_corner + u * horiizonal + v * vertical);
	}

public:
	vec3 lower_left_corner;
	vec3 horiizonal;
	vec3 vertical;
	vec3 origin;
};