#include "stdafx.h"
#include "../ObjectAdapter/ModernGraphicsObjectAdapter.h"
#include "../ObjectAdapter/shape_drawing_lib.h"
#include <sstream>

struct RendererFixture
{
	std::stringstream output;
	modern_graphics_lib::CModernGraphicsRenderer renderer;
	RendererFixture()
		: renderer(output)
	{
	}
};

struct ObjectAdapterFixture : RendererFixture
{
	app::CModernGraphicsObjectAdapter adapter;
	ObjectAdapterFixture()
		: adapter(renderer)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(ObjectAdapter, ObjectAdapterFixture)

BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_trying_to_draw_if_drawing_isnt_begin)
{
	BOOST_CHECK_THROW(adapter.LineTo(1, 2), std::logic_error);
}

BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_trying_to_end_draw_if_drawing_isnt_begin)
{
	BOOST_CHECK_THROW(renderer.EndDraw(), std::logic_error);
}

struct when_drawing_started_ : ObjectAdapterFixture
{
	when_drawing_started_()
	{
		renderer.BeginDraw();
	}
};

BOOST_FIXTURE_TEST_SUITE(when_drawing_started, when_drawing_started_)

BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_trying_to_begin_drawing_twice)
{
	BOOST_CHECK_THROW(renderer.BeginDraw(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(can_move_to_and_draw_line)
{
	adapter.MoveTo(5, 10);
	adapter.LineTo(1, 2);
	adapter.LineTo(3, 4);
	adapter.MoveTo(1, 1);
	adapter.LineTo(5, 6);
	std::string expected = R"(<draw>
  <line fromX="5" fromY="10" toX="1" toY="2">
    <color r="0" g="0" b="0" a="1" />
  </line>
  <line fromX="1" fromY="2" toX="3" toY="4">
    <color r="0" g="0" b="0" a="1" />
  </line>
  <line fromX="1" fromY="1" toX="5" toY="6">
    <color r="0" g="0" b="0" a="1" />
  </line>
)";
	BOOST_CHECK_EQUAL(output.str(), expected);
}

BOOST_AUTO_TEST_CASE(when_line_is_drawn_without_move_to_start_position_shoul_be_0_0)
{
	adapter.LineTo(1, 2);
	std::string expected = R"(<draw>
  <line fromX="0" fromY="0" toX="1" toY="2">
    <color r="0" g="0" b="0" a="1" />
  </line>
)";
	BOOST_CHECK_EQUAL(output.str(), expected);
}

BOOST_AUTO_TEST_CASE(can_set_color)
{
	adapter.SetColor(0xff00ff);
	adapter.LineTo(1, 2);
	std::string expected = R"(<draw>
  <line fromX="0" fromY="0" toX="1" toY="2">
    <color r="1" g="0" b="1" a="1" />
  </line>
)";

	BOOST_CHECK_EQUAL(output.str(), expected);
}

BOOST_AUTO_TEST_CASE(can_end_draw)
{
	renderer.EndDraw();
	BOOST_CHECK_EQUAL(output.str(), "<draw>\n</draw>\n");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()