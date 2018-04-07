#pragma once
#include"Point.h"

struct Rectangle : public Point
{
	int width;
	int height;

	Rectangle(std::string name) :
		Point(name, Tags::RECT)
	{

	}
};