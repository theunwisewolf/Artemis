#pragma once

#include "Tag.h"

struct Point : public Tag
{
	double x = 0.0f;
	double y = 0.0f;

	uint32_t color = 0xffffff;

	float scale = 1.0f;

	Point(Tags type = Tags::POINT) :
		Tag("", type)
	{

	}

	Point(double _x, double _y, Tags type = Tags::POINT) :
		x(_x),
		y(_y),
		Tag("", type)
	{

	}

	Point(std::string name, double _x, double _y, Tags type = Tags::POINT) :
		x(_x),
		y(_y),
		Tag(name, type)
	{

	}

	Point(std::string name, Tags type = Tags::POINT) :
		Tag(name, type)
	{

	}
};

// Utility method for ear clipping
namespace mapbox {
	namespace util {

		template <>
		struct nth<0, Point> {
			inline static auto get(const Point &t) {
				return t.x;
			};
		};
		template <>
		struct nth<1, Point> {
			inline static auto get(const Point &t) {
				return t.y;
			};
		};

	} // namespace util
} // namespace mapbox