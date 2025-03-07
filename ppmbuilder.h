#pragma once

#include <fstream>
#include <iostream>
#include <string>


class ppmbuilder
{
public:
	ppmbuilder(std::string name) : filename(name) {	}

	void ppmbuild(double color[], int width, int height)
	{
		std::ofstream file(filename);
		if (file.is_open())
		{
			file << "P3\n" << width << ' ' << height << "\n255\n";
			for (int i = 0; i < width * height; i++)
			{
				int pixelindex = i * 3;
				double channelr = color[pixelindex];
				double channelg = color[pixelindex + 1];
				double channelb = color[pixelindex + 2];
				//std::cout << channelr << ' ' << channelg << ' ' << channelb << ' ' <<  pixelindex << ' ' << i << std::endl;
				file << static_cast<int>(256 * clamp(channelr, 0.0, 0.999)) << ' ' //static_cast<type>(value)显式类型转换
					<< static_cast<int>(256 * clamp(channelg, 0.0, 0.999)) << ' '
					<< static_cast<int>(256 * clamp(channelb, 0.0, 0.999)) << "\n";

			}
			file.close();
			std::cout << std::endl <<"complished" << std::endl;
		}
	}
public:
	std::string filename;
};