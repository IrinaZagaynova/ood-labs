#include "stdafx.h"
#include "../Slides/Group.h"
#include "MockCanvas.h"
#include "../Slides/Triangle.h"
#include "../Slides/Rectangle.h"
#include "../Slides/Ellipse.h"

struct EmptyGroupFixture
{
	CGroup group;
};

BOOST_FIXTURE_TEST_SUITE(EmptyGroup, EmptyGroupFixture)
	
	BOOST_AUTO_TEST_CASE(GetShapeCount_should_return_0)
	{
		BOOST_CHECK_EQUAL(group.GetShapesCount(), 0);
	}

	BOOST_AUTO_TEST_CASE(can_get_group)
	{
		auto groupPtr = std::make_shared<CGroup>();
		BOOST_CHECK_EQUAL(groupPtr->GetGroup(), groupPtr);
	}

	BOOST_AUTO_TEST_CASE(frame_in_empty_group_shuldnt_have_value)
	{
		BOOST_CHECK(!group.GetFrame().has_value());
	}

	BOOST_AUTO_TEST_CASE(empty_group_shuldnt_have_line_style_color)
	{
		BOOST_CHECK(!group.GetLineStyle()->GetColor().has_value());
	}

	BOOST_AUTO_TEST_CASE(empty_group_shuldnt_have_line_width)
	{
		BOOST_CHECK(!group.GetLineStyle()->GetLineWidth().has_value());
	}

	BOOST_AUTO_TEST_CASE(empty_group_shuldnt_have_fill_style_color)
	{
		BOOST_CHECK(!group.GetFillStyle()->GetColor().has_value());
	}

	BOOST_AUTO_TEST_CASE(can_insert_shape)
	{
		std::shared_ptr<IShape> triangle = std::make_shared<CTriangle>(Point({ 1, 2 }), Point({ 3, 4 }), Point({ 1, 5 }));
		group.InsertShape(triangle, 0);
		BOOST_CHECK_EQUAL(group.GetShapesCount(), 1);	
		BOOST_CHECK(group.GetShapeAtIndex(0) == triangle);
	}

	BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_trying_to_get_shape_from_incorrect_position)
	{
		BOOST_CHECK_THROW(group.GetShapeAtIndex(0), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_trying_to_insert_shapes_into_incorrect_position)
	{
		std::shared_ptr<IShape> triangle = std::make_shared<CTriangle>(Point({ 1, 2 }), Point({ 3, 4 }), Point({ 1, 5 }));
		BOOST_CHECK_THROW(group.InsertShape(triangle, 1), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(should_throw_an_exception_when_trying_to_remove_shape_at_incorrect_index)
	{
		BOOST_CHECK_THROW(group.RemoveShapeAtIndex(0), std::out_of_range);
	}

	BOOST_AUTO_TEST_CASE(should_not_draw_anything)
	{
		std::ostringstream strm;
		CMockCanvas canvas(strm);
		BOOST_CHECK_EQUAL(strm.str(), "");
	}

BOOST_AUTO_TEST_SUITE_END()

struct TrianglePtr
{
	std::shared_ptr<IShape> triangle = std::make_shared<CTriangle>(Point({ 1, 2 }), Point({ 3, 4 }), Point({ 1, 5 }));
};

struct RectanglePtr
{
	std::shared_ptr<IShape> rectangele = std::make_shared<CRectangle>(Point({ 2, 1 }), 0.5, 0.5);
};

struct EllipsePtr
{
	std::shared_ptr<IShape> ellipse = std::make_shared<CEllipse>(Point({ 0, 0 }), 1, 1);
};

struct group_with_shapes_ : TrianglePtr, RectanglePtr, EllipsePtr, EmptyGroupFixture
{
	group_with_shapes_()
	{
		group.InsertShape(triangle, 0);
		group.InsertShape(rectangele, 1);
		group.InsertShape(ellipse, 2);
		group.GetLineStyle()->SetColor({ 1, 0, 0, 1 });
		group.GetFillStyle()->SetColor({ 0, 1, 0, 1 });
		group.GetLineStyle()->Enable(true);
		group.GetFillStyle()->Enable(true);
	}
};

void VerifyFrames(std::optional<RectD> frame1, std::optional<RectD> frame2)
{
	if (!frame1.has_value() && !frame2.has_value())
	{
		return;
	}
	else if (frame1.has_value() && frame2.has_value())
	{
		BOOST_CHECK_EQUAL(frame1->left, frame2->left);
		BOOST_CHECK_EQUAL(frame1->top, frame2->top);
		BOOST_CHECK_EQUAL(frame1->width, frame2->width);
		BOOST_CHECK_EQUAL(frame1->height, frame2->height);
	}
}

BOOST_FIXTURE_TEST_SUITE(group_with_shapes, group_with_shapes_)

	BOOST_AUTO_TEST_CASE(can_get_shapes_count)
	{
		BOOST_CHECK_EQUAL(group.GetShapesCount(), 3);
	}

	BOOST_AUTO_TEST_CASE(can_get_shape_at_index)
	{
		BOOST_CHECK_EQUAL(group.GetShapeAtIndex(0), triangle);
		BOOST_CHECK_EQUAL(group.GetShapeAtIndex(1), rectangele);
		BOOST_CHECK_EQUAL(group.GetShapeAtIndex(2), ellipse);
	}

	BOOST_AUTO_TEST_CASE(can_get_outline_color)
	{
		BOOST_CHECK(group.GetLineStyle()->GetColor() == RGBAColor(1, 0, 0, 1));
	}

	BOOST_AUTO_TEST_CASE(can_get_line_width)
	{
		BOOST_CHECK(group.GetLineStyle()->GetLineWidth() == 1);
	}

	BOOST_AUTO_TEST_CASE(can_get_fill_color)
	{
		BOOST_CHECK(group.GetFillStyle()->GetColor() == RGBAColor(0, 1, 0, 1));
	}

	BOOST_AUTO_TEST_CASE(GetOutlineColor_should_return_nullopt_if_shapes_in_group_have_different_colors)
	{
		triangle->GetLineStyle()->SetColor(RGBAColor(1, 1, 1, 1));
		BOOST_CHECK(!group.GetLineStyle()->GetColor().has_value());
	}

	BOOST_AUTO_TEST_CASE(GetLineWidth_should_return_nullopt_if_shapes_in_group_have_different_line_widths)
	{
		triangle->GetLineStyle()->SetLineWidth(10);
		BOOST_CHECK(!group.GetLineStyle()->GetLineWidth().has_value());
	}

	BOOST_AUTO_TEST_CASE(GetFillColor_should_return_nullopt_if_shapes_in_group_have_different_colors)
	{
		triangle->GetFillStyle()->SetColor({ 1, 1, 1, 1 });
		BOOST_CHECK(!group.GetFillStyle()->GetColor().has_value());
	}

	BOOST_AUTO_TEST_CASE(can_get_group_frame)
	{
		VerifyFrames(group.GetFrame(), RectD({ -1, 5, 4, 6 }));
	}

	BOOST_AUTO_TEST_CASE(can_set_group_frame)
	{
		group.SetFrame({-5, 10, 8, 6});
		VerifyFrames(group.GetFrame(), RectD({ -5, 10, 8, 8 }));
		VerifyFrames(triangle->GetFrame(), RectD({ -1, 10, 4, 3 }));
		VerifyFrames(rectangele->GetFrame(), RectD({ 1, 6, 1, 0.5 }));
		VerifyFrames(ellipse->GetFrame(), RectD({ -5, 6, 2, 4 }));
	}

	BOOST_AUTO_TEST_CASE(can_remove_shape_from_group)
	{
		group.RemoveShapeAtIndex(1);
		BOOST_CHECK_EQUAL(group.GetShapesCount(), 2);
		BOOST_CHECK_EQUAL(group.GetShapeAtIndex(1), ellipse);
	}

	BOOST_AUTO_TEST_CASE(can_draw_shapes)
	{
		std::ostringstream strm;
		CMockCanvas canvas(strm);
		group.Draw(canvas);
		std::string expected = R"(fill color: 0 1 0 1
filling poligon
line color: 1 0 0 1
drawing line
drawing line
drawing line
fill color: 0 1 0 1
filling poligon
line color: 1 0 0 1
drawing line
drawing line
drawing line
drawing line
fill color: 0 1 0 1
filling ellipse
line color: 1 0 0 1
drawing ellipse
)";
		BOOST_CHECK_EQUAL(strm.str(), expected);
	}

	BOOST_AUTO_TEST_CASE(can_change_style_for_all_shapes_in_group)
	{
		group.GetLineStyle()->SetColor(RGBAColor(0.1, 0.2, 0.3, 0.4));
		group.GetFillStyle()->SetColor(RGBAColor(0.5, 0.6, 0.7, 0.8));
		group.GetLineStyle()->SetLineWidth(5);

		BOOST_CHECK(*group.GetLineStyle()->GetColor() == RGBAColor(0.1, 0.2, 0.3, 0.4));
		BOOST_CHECK(*group.GetFillStyle()->GetColor() == RGBAColor(0.5, 0.6, 0.7, 0.8));
		BOOST_CHECK_EQUAL(*group.GetLineStyle()->GetLineWidth(), 5);

		for (size_t i = 0; i < group.GetShapesCount(); i++)
		{
			BOOST_CHECK(*group.GetShapeAtIndex(i)->GetLineStyle()->GetColor() == *group.GetLineStyle()->GetColor());
			BOOST_CHECK(*group.GetShapeAtIndex(i)->GetFillStyle()->GetColor() == *group.GetFillStyle()->GetColor());
			BOOST_CHECK_EQUAL(*group.GetLineStyle()->GetLineWidth(), 5);
		}
	}
	
BOOST_AUTO_TEST_SUITE_END()