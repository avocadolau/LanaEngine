#pragma once

#include "lnpch.h"
#include <vector>

namespace Lanna
{
	struct Grid
	{
		std::vector<float> vbo_data;
		std::vector<int> ebo_data;
		Lanna::Framebuffer* buff;
		int gridSize = 10;
		float spacing = 1.0f;

		unsigned int vao = -1;				// vertex array object
		unsigned int ebo = -1;				// element buffer object
		unsigned int vbo = -1;				// vertex buffer object

		Grid() {

		}
		void Init()
		{
			for (int i = -gridSize; i <= gridSize; i++)
			{
				for (int j = -gridSize; j <= gridSize; j++)
				{
					ebo_data.push_back(i*spacing);
					ebo_data.push_back(0.0f);
					ebo_data.push_back(j * spacing);
				}

			}
		}
		~Grid() {
			vbo_data.clear();
			ebo_data.clear();

		}
	};
}