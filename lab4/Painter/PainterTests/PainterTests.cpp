#include "stdafx.h"
#include "../Painter/Painter.h"
#include "../Painter/PictureDraft.h"
#include "../Painter/Triangle.h"
#include "../Painter/Ellipse.h"
#include "../PainterTests/MockCanvas.h"

using namespace std;

struct Picture_draft_
{
	CPictureDraft draft;
};

struct after_adding_a_shape_ : Picture_draft_
{
	after_adding_a_shape_()
	{
		draft.AddShape(make_unique<CTriangle>(SPoint({ -0.3, -0.9 }), SPoint({ -0.9, -0.5 }), SPoint({ -0.5, -0.3 }), Color::Red));
		draft.AddShape(make_unique<CEllipse>(SPoint({ 0,0 }), 0.3, 0.5, Color::Blue));
	}
};

BOOST_FIXTURE_TEST_SUITE(after_adding_a_shape, after_adding_a_shape_)
BOOST_AUTO_TEST_CASE(should_draw_added_shapes)
{
	std::ostringstream strm;
	MockCanvas canvas(strm);
	CPainter paiter;
	paiter.DrawPicture(draft, canvas);

	const auto expected = R"(color is red
draw a line from -0.3 -0.9 to -0.9 -0.5
draw a line from -0.9 -0.5 to -0.5 -0.3
draw a line from -0.5 -0.3 to -0.3 -0.9
color is blue
draw an ellipse centered at 0 0, a width of 0.3, a height of 0.5
)";
	BOOST_CHECK_EQUAL(strm.str(), expected);
}
BOOST_AUTO_TEST_SUITE_END()