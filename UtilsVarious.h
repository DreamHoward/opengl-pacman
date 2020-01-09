#pragma once
#include <vector>
#include <list>
#include <limits>
#include "Map.h"
#include <GL/glut.h>
#include "glm/glm/vec2.hpp"
#include "glm/glm/vec3.hpp"
#include <Math.h>

namespace Utils
{
	
	glm::vec3 VgridPosToWorldPos(glm::vec2 gridPos)
	{
		return glm::vec3(gridPos.x, 0.0f, gridPos.y) * 100.0f + 50.0f;
	}

	glm::vec2 VworldPosToGridPos(glm::vec3 worldPos)
	{
		return glm::vec2(floor(worldPos.x / 100.0f),
			floor(worldPos.z / 100.0f));
	}

	int VmanhattanDistance(glm::vec2 a, glm::vec2 b)
	{
		return fabs(a.x - b.x) + fabs(a.y - b.y);
	}

	glm::vec2 VaStar(const glm::vec2& start, const glm::vec2& end, const Map& map)
	{
		// Boundary check
		if (start.x < 0 || start.x >= map.GetWidth() ||
			start.y < 0 || start.y >= map.GetHeight() ||
			end.x < 0 || end.x >= map.GetWidth() ||
			end.y < 0 || end.y >= map.GetHeight() ||
			start == end)
			return glm::vec2(-1,-1);

		// Data initialization
		std::vector<std::vector<float>> f, g, h;
		std::vector<std::vector<glm::vec2>> comeFrom;
		for (int i = 0; i < map.GetHeight(); i++)
		{
			f.push_back(std::vector<float>(map.GetWidth(), std::numeric_limits<float>::infinity()));
			g.push_back(std::vector<float>(map.GetWidth(), std::numeric_limits<float>::infinity()));
			h.push_back(std::vector<float>());
			comeFrom.push_back(std::vector<glm::vec2>(map.GetWidth()));

			for (int j = 0; j < map.GetWidth(); j++)
				h[i].push_back(VmanhattanDistance(glm::vec2(j, i), end));
		}
		g[start.y][start.x] = 0;
		f[start.y][start.x] = h[start.y][start.x] + g[start.y][start.x];

		// Search
		std::list<glm::vec2> open;
		open.push_back(start);

		while (!open.empty())
		{
			// Pick the node that has the lowest f
			glm::vec2 toBeExplored = *open.begin();
			for (std::list<glm::vec2>::iterator i = open.begin(); i != open.end(); i++)
			{
				if (f[i->y][i->x] < f[toBeExplored.y][toBeExplored.x])
					toBeExplored = *i;
			}
			open.remove(toBeExplored);

			// Found
			if (toBeExplored == end)
			{
				std::vector<glm::vec2> path;
				for (glm::vec2 node = end; node != start; node = comeFrom[node.y][node.x])
				{
					path.push_back(node);
				}
				//path.push_back(start);
				//std::reverse(path.begin(), path.end());
				return path.back();
			}

			// Explore every direction
			const glm::vec2 walkDir[4] = { glm::vec2(0, 1), glm::vec2(1, 0), glm::vec2(0, -1), glm::vec2(-1, 0) };
			for (int i = 0; i < 4; i++)
			{
				glm::vec2 destination = toBeExplored + walkDir[i];
				float cost = map.GetCost(toBeExplored.y, toBeExplored.x, destination.y, destination.x);
				if (cost == std::numeric_limits<float>::infinity()) continue;

				float newG = cost + g[toBeExplored.y][toBeExplored.x];
				float newF = newG + h[destination.y][destination.x];
				if (newF < f[destination.y][destination.x])
				{
					f[destination.y][destination.x] = newF;
					g[destination.y][destination.x] = newG;
					comeFrom[destination.y][destination.x] = toBeExplored;
					open.remove(destination);
					open.push_back(destination);
				}
			}
		}

		// No such path
		return glm::vec2(-1,-1);
	}
}