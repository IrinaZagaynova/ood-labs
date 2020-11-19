#pragma once
#include <iomanip>

struct Point
{
	double x;
	double y;
};

template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;
};
typedef Rect<double> RectD;

class RGBAColor
{
public:
	RGBAColor(float r, float g, float b, float a) :r(r), g(g), b(b), a(a) {}
	float r, g, b, a;

	bool operator ==(const RGBAColor& color)const
	{
		return ((r == color.r) && (g == color.g) && (b == color.b) && (a == color.a));
	}

	bool operator !=(const RGBAColor& color)const
	{
		return !(*this == color);
	}
};