#include "stdafx.h"
#include "../ClassAdapter/ModernGraphicsClassAdapter.h"
#include "../ClassAdapter/shape_drawing_lib.h"
#include <sstream>

struct ClassAdapterFixture
{
	std::stringstream output;
	app::CModernGraphicsClassAdapter adapter;
	ClassAdapterFixture()
		: adapter(output)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(ClassAdapter, ClassAdapterFixture)

BOOST_AUTO_TEST_CASE(can_move_to_before_draw_line)
{
	adapter.MoveTo(5, 10);
	adapter.LineTo(1, 2);
	std::string expected = R"(<draw>
  <line fromX="5" fromY="10" toX="1" toY="2">
    <color r="0" g="0" b="0" a="1" />
  </line>
)";
	BOOST_CHECK_EQUAL(output.str(), expected);
}

BOOST_AUTO_TEST_CASE(can_move_to_after_draw_line)
{
	adapter.LineTo(3, 4);
	adapter.MoveTo(1, 1);
	adapter.LineTo(5, 6);
	std::string expected = R"(<draw>
  <line fromX="0" fromY="0" toX="3" toY="4">
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

BOOST_AUTO_TEST_SUITE_END()