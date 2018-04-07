#pragma once

#include "Point.h"

#include <vector>

struct Ellipse : public Point
{
	float rx;
	float ry;

	uint32_t lod = 24;

	std::vector<Point> uvs;
	std::vector<Point> vertices;
	std::vector<uint32_t> indices;

	Ellipse(std::string name) :
		Point(name, Tags::ELLIPSE)
	{

	}
};
