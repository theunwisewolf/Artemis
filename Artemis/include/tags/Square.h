#pragma once
#include"Point.h"
struct Square : public Point
{
	int sidelength;

	Square(std::string name) :
		Point(name, Tags::SQUARE)
	{

	}
};
