#include "stdafx.h"
#include "../Painter/PictureDraft.h"
#include "../Painter/Shape.h"
#include "../Painter/Rectangle.h"
#include "../Painter/Triangle.h"
#include "../Painter/Ellipse.h"
#include "../Painter/RegularPolygon.h"

using namespace std;
struct Picture_draft_
{
	CPictureDraft draft;
};

BOOST_FIXTURE_TEST_SUITE(Picture_draft, Picture_draft_)
BOOST_AUTO_TEST_SUITE(by_default)
BOOST_AUTO_TEST_CASE(is_empty)
{
	BOOST_CHECK(draft.IsEmpty());
}
BOOST_AUTO_TEST_CASE(has_equal_begin_and_end_iterators)
{
	BOOST_CHECK(draft.begin() == draft.end());
}
BOOST_AUTO_TEST_SUITE_END()

struct after_adding_a_shape_ : Picture_draft_
{
	unique_ptr<CShape> rectangle = make_unique<CRectangle>(SPoint({ 0.3, 0.9 }), 0.5, 0.4, Color::Yellow);
	CShape& refRectangle = *rectangle;
	unique_ptr<CShape> triangle = make_unique<CTriangle>(SPoint({ -0.3, -0.9 }), SPoint({ -0.9, -0.5 }), SPoint({ -0.5, -0.3 }), Color::Red);
	CShape& refTriangle = *triangle;
	unique_ptr<CShape> ellipse = make_unique<CEllipse>(SPoint({0,0}), 0.3, 0.3, Color::Blue);
	CShape& refEllipse = *ellipse;
	unique_ptr<CShape> regularPolygon = make_unique<CRegularPolygon>(SPoint({ 0,0 }), 5, 0.3, Color::Green);
	CShape& refRegularPolygon = *regularPolygon;

	after_adding_a_shape_()
	{
		draft.AddShape(move(rectangle));
		draft.AddShape(move(triangle));
		draft.AddShape(move(ellipse));
		draft.AddShape(move(regularPolygon));
	}
};
BOOST_FIXTURE_TEST_SUITE(after_adding_a_shape, after_adding_a_shape_)
BOOST_AUTO_TEST_CASE(becomes_not_empty)
{
	BOOST_CHECK(!draft.IsEmpty());
}
BOOST_AUTO_TEST_CASE(has_different_begin_and_end_iterators)
{
	BOOST_CHECK(draft.begin() != draft.end());
}
BOOST_AUTO_TEST_CASE(allows_iteration_across_added_shapes)
{
	auto it = draft.begin();
	BOOST_CHECK_EQUAL(addressof(*(it++)), addressof(refRectangle));
	BOOST_REQUIRE(it != draft.end());
	BOOST_CHECK_EQUAL(addressof(*(it++)), addressof(refTriangle));
	BOOST_REQUIRE(it != draft.end());
	BOOST_CHECK_EQUAL(addressof(*(it++)), addressof(refEllipse));
	BOOST_REQUIRE(it != draft.end());
	BOOST_CHECK_EQUAL(addressof(*(it++)), addressof(refRegularPolygon));
	BOOST_REQUIRE(it == draft.end());
}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()