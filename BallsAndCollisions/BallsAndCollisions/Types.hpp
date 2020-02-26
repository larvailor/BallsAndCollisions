#pragma once

enum class FigureType
{
	CIRCLE,
	SQUARE
};

struct Point
{
	float x;
	float y;
	
	Point() : x(0), y(0) { }
	Point(float x, float y) : x(x), y(y) { }
};

typedef float Length;
typedef Length Radius;
typedef float Velocity;
typedef float Weight;
