#pragma once

#include "Point.h"
#include "Tag.h"

#include <vector>

struct Polygon : public Point
{
	std::vector<Point> vertices;
	std::vector<uint32_t> indices;

	Polygon(std::string name) :
		Point(name, Tags::POLYGON)
	{

	}
};