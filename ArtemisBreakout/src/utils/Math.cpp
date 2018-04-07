#include "Math.h"

float lerp(float start, float stop, float amount)
{
	return amount * (stop - start) + start;
}

float inverselerp(float start, float stop, float value)
{
	return (value - start) / (stop - start);
}