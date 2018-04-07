#pragma once

#include "Point.h"
#include "Tag.h"

struct Line : public Tag
{
	Point p1;
	Point p2;

	Line(std::string name) :
		Tag(name, Tags::LINE)
	{

	}
};