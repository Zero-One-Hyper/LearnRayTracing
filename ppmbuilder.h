#pragma once

#include <fstream>
#include <iostream>
#include <string>


class ppmbuilder
{
public:
	ppmbuilder(std::string name) : filename(name) {	}

	void ppmbuild(double* color, int width, int height)
	{
		std::ofstream file(filename);
		if (file.is_open())
		{
			file << "P3\n" << width << ' ' << height << "\n255\n";
			for (int i = 0; i < width * height * 3; i++)
			{

				double channelr = color[i];
				double channelg = color[i + 1];
				double channelb = color[i + 2];
				file << channelr << " " << channelg << " " << channelb << "\n";

			}
			file.close();
			std::cout << "complished" << std::endl;
		}
	}
public:
	std::string filename;
};