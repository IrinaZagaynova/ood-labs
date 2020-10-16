#include "stdafx.h"
#include "../Painter/Shape.h"
#include "../Painter/Rectangle.h"
#include "../Painter/Triangle.h"
#include "../Painter/Ellipse.h"
#include "../Painter/RegularPolygon.h"
#include "../Painter/Color.h"
#include "../PainterTests/MockCanvas.h"

using namespace std;

struct Rectangle_
{
	const SPoint expectedLeftTopCorner = { 0.3, 0.9 };
	const double expectedWidth = 0.5;
	const double expectedHeight = 0.4;
	const Color expectedColor = Color::Yellow;
	const CRectangle rectangle;
	Rectangle_()
		: rectangle(expectedLeftTopCorner, expectedWidth, expectedHeight, expectedColor)
	{}
};

BOOST_FIXTURE_TEST_SUITE(Rectangle, Rectangle_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&rectangle));
}
BOOST_AUTO_TEST_CASE(must_be_initialized_with_given_params)
{
	BOOST_CHECK_EQUAL(rectangle.GetWidth(), expectedWidth);
	BOOST_CHECK_EQUAL(rectangle.GetHeight(), expectedHeight);
	BOOST_CHECK_EQUAL(rectangle.GetLeftTopCorner().x, expectedLeftTopCorner.x);
	BOOST_CHECK_EQUAL(rectangle.GetLeftTopCorner().y, expectedLeftTopCorner.y);
	BOOST_CHECK(rectangle.GetColor() == expectedColor);
}
BOOST_AUTO_TEST_CASE(draw_recrangle_tests)
{
	std::ostringstream strm;
	MockCanvas canvas(strm);
	rectangle.Draw(canvas);
	const auto expected = R"(color is yellow
draw a line from 0.3 0.9 to 0.8 0.9
draw a line from 0.8 0.9 to 0.8 0.5
draw a line from 0.8 0.5 to 0.3 0.5
draw a line from 0.3 0.5 to 0.3 0.9
)";
	BOOST_CHECK_EQUAL(strm.str(), expected);
}
BOOST_AUTO_TEST_SUITE_END()

struct Triangle_
{
	const SPoint vertex1 = { -0.3, -0.9 };
	const SPoint vertex2 = { -0.9, -0.5 };
	const SPoint vertex3 = { -0.5, -0.3 };
	const Color color = Color::Red;
	const CTriangle triangle;
	Triangle_()
		: triangle(vertex1, vertex2, vertex3, color)
	{}
};
BOOST_FIXTURE_TEST_SUITE(Triangle, Triangle_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&triangle));
}
BOOST_AUTO_TEST_CASE(must_be_initialized_with_given_params)
{
	BOOST_CHECK_EQUAL(triangle.GetVertex1().x, vertex1.x);
	BOOST_CHECK_EQUAL(triangle.GetVertex1().y, vertex1.y);
	BOOST_CHECK_EQUAL(triangle.GetVertex2().x, vertex2.x);
	BOOST_CHECK_EQUAL(triangle.GetVertex2().y, vertex2.y);
	BOOST_CHECK_EQUAL(triangle.GetVertex3().x, vertex3.x);
	BOOST_CHECK_EQUAL(triangle.GetVertex3().y, vertex3.y);
	BOOST_CHECK(triangle.GetColor() == color);
}
BOOST_AUTO_TEST_CASE(draw_triangle_tests)
{
	std::ostringstream strm;
	MockCanvas canvas(strm);
	triangle.Draw(canvas);
	const auto expected = R"(color is red
draw a line from -0.3 -0.9 to -0.9 -0.5
draw a line from -0.9 -0.5 to -0.5 -0.3
draw a line from -0.5 -0.3 to -0.3 -0.9
)";
	BOOST_CHECK_EQUAL(strm.str(), expected);
}
BOOST_AUTO_TEST_SUITE_END()

struct Ellipse_
{
	const SPoint center = { 0, 0 };
	const double horizontalRadius = 0.3;
	const double verticalRadius = 0.5;
	const Color color = Color::Red;
	const CEllipse ellipse;
	Ellipse_()
		: ellipse(center, horizontalRadius, verticalRadius, color)
	{}
};
BOOST_FIXTURE_TEST_SUITE(Ellipse, Ellipse_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&ellipse));
}
BOOST_AUTO_TEST_CASE(must_be_initialized_with_given_params)
{
	BOOST_CHECK_EQUAL(ellipse.GetCenter().x, center.x);
	BOOST_CHECK_EQUAL(ellipse.GetCenter().y, center.y);
	BOOST_CHECK_EQUAL(ellipse.GetHorizontalRadius(), horizontalRadius);
	BOOST_CHECK_EQUAL(ellipse.GetVerticalRadius(), verticalRadius);
	BOOST_CHECK(ellipse.GetColor() == color);
}
BOOST_AUTO_TEST_CASE(draw_ellipse_tests)
{
	std::ostringstream strm;
	MockCanvas canvas(strm);
	ellipse.Draw(canvas);
	const auto expected = R"(color is red
draw an ellipse centered at 0 0, a width of 0.3, a height of 0.5
)";
	BOOST_CHECK_EQUAL(strm.str(), expected);
}
BOOST_AUTO_TEST_SUITE_END()

struct RegularPolygon_
{
	const SPoint center = { 0, 0 };
	const size_t vertexCount = 5;
	const double radius = 0.3;
	const Color color = Color::Red;
	const CRegularPolygon regularPolygon;
	RegularPolygon_()
		: regularPolygon(center, vertexCount, radius, color)
	{}
};
BOOST_FIXTURE_TEST_SUITE(RegularPolygon, RegularPolygon_)
BOOST_AUTO_TEST_CASE(is_a_shape)
{
	BOOST_CHECK(static_cast<const CShape*>(&regularPolygon));
}
BOOST_AUTO_TEST_CASE(must_be_initialized_with_given_params)
{
	BOOST_CHECK_EQUAL(regularPolygon.GetCenter().x, center.x);
	BOOST_CHECK_EQUAL(regularPolygon.GetCenter().y, center.y);
	BOOST_CHECK_EQUAL(regularPolygon.GetVertexCount(), vertexCount);
	BOOST_CHECK_EQUAL(regularPolygon.GetRadius(), radius);
}
BOOST_AUTO_TEST_CASE(draw_regular_polygon_tests)
{
	std::ostringstream strm;
	MockCanvas canvas(strm);
	regularPolygon.Draw(canvas);
	const auto expected = R"(color is red
draw a line from 0.3 0 to 0.0927051 0.285317
draw a line from 0.0927051 0.285317 to -0.242705 0.176336
draw a line from -0.242705 0.176336 to -0.242705 -0.176336
draw a line from -0.242705 -0.176336 to 0.0927051 -0.285317
draw a line from 0.3 0 to 0.0927051 -0.285317
)";
	BOOST_CHECK_EQUAL(strm.str(), expected);
}
BOOST_AUTO_TEST_SUITE_END()