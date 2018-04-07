#pragma once

#include "Point.h"

struct Triangle : public Tag
{
	Point p1;
	Point p2;
	Point p3;

	Triangle(std::string name) :
		Tag(name, Tags::TRIANGLE)
	{

	}
};