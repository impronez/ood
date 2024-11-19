#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"

#include "../CEllipse.h"
#include "../CRectangle.h"
#include "../CTriangle.h"
#include "../CRegularPolygon.h"
#include "../CPictureDraft.h"
#include "../CPainter.h"
#include "../CShapeFactory.h"
#include "../CDesigner.h"

class TestCanvas : public ICanvas
{
public:
	void SetColor(const CColor color) override
	{
		m_result.push_back("set color");
	}

	void DrawLine(double fromX, double fromY, double toX, double toY) override
	{
		m_result.push_back("draw line");

	}

	void DrawEllipse(double cx, double cy, double rx, double ry) override
	{
		m_result.push_back("draw ellipse");

	}

	std::vector<std::string> GetResult() const
	{
		return m_result;
	}
private:
	std::vector<std::string> m_result = {};
};

bool AreEqualPoints(Point p1, Point p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}

bool AreEqualColors(CColor c1, CColor c2)
{
	return c1.GetStringView() == c2.GetStringView();
}

TEST_CASE("Rectangle create")
{
	CColor color = CColor();
	Point leftTop(10, 20);
	double width = 30;
	double height = 50;

	CRectangle rectangle(color, leftTop, width, height);

	REQUIRE(rectangle.GetHeight() == height);
	REQUIRE(rectangle.GetWidth() == width);
	REQUIRE(AreEqualPoints(rectangle.GetLeftTop(), leftTop));
	REQUIRE(AreEqualColors(rectangle.GetColor(), color));
}

TEST_CASE("Ellipse create")
{
	CColor color = CColor();
	Point center(50, 50);
	double horizontalRadius = 30;
	double verticalRadius = 20;

	CEllipse ellipse(color, center, horizontalRadius, verticalRadius);

	REQUIRE(ellipse.GetHorizontalRadius() == horizontalRadius);
	REQUIRE(ellipse.GetVerticalRadius() == verticalRadius);
	REQUIRE(AreEqualColors(ellipse.GetColor(), color));
	REQUIRE(AreEqualPoints(ellipse.GetCenter(), center));
}

TEST_CASE("Triangle create")
{
	CColor color = CColor();
	Point vertex1(10, 20);
	Point vertex2(40, 20);
	Point vertex3(25, 50);

	CTriangle triangle(color, vertex1, vertex2, vertex3);

	REQUIRE(AreEqualPoints(triangle.GetVertex1(), vertex1));
	REQUIRE(AreEqualPoints(triangle.GetVertex2(), vertex2));
	REQUIRE(AreEqualPoints(triangle.GetVertex3(), vertex3));
	REQUIRE(AreEqualColors(triangle.GetColor(), color));
}

TEST_CASE("Regular polygon create")
{
	CColor color = CColor();
	Point center(50, 50);
	int verticesCount = 5;
	double radius = 30.0;

	CRegularPolygon regularPolygon(color, center, verticesCount, radius);

	REQUIRE(regularPolygon.GetRadius() == radius);
	REQUIRE(AreEqualColors(regularPolygon.GetColor(), color));
	REQUIRE(AreEqualPoints(regularPolygon.GetCenter(), center));
	REQUIRE(regularPolygon.GetPointsCount() == verticesCount);
}

TEST_CASE("Test picture draft")
{
	SECTION("Picture without shapes")
	{
		CPictureDraft pictureDraft;
		REQUIRE(pictureDraft.begin() == pictureDraft.end());
		REQUIRE(pictureDraft.GetShapesCount() == 0);
	}

	SECTION("Picture with shapes")
	{
		CPictureDraft pictureDraft;
		CColor color = CColor();
		Point center(12, 12);

		CRegularPolygon regularPolygon(CColor(), center, 4, 12);
		auto regularPolygonPtr = std::make_unique<CRegularPolygon>(regularPolygon);

		CRectangle rectangle(CColor(), {12, 12}, 4, 12);
		auto rectanglePtr = std::make_unique<CRectangle>(rectangle);

		WHEN("Adding regular polygon")
		{
			REQUIRE_NOTHROW(pictureDraft.AddShape(std::move(regularPolygonPtr)));
			REQUIRE_NOTHROW(pictureDraft.AddShape(std::move(rectanglePtr)));

			THEN("picture has 2 items")
			{
				REQUIRE(pictureDraft.GetShapesCount() == 2);
			}

			THEN("picture draft has regular polygon")
			{
				auto shape = dynamic_cast<CRegularPolygon&>(pictureDraft.GetShape(0));

				REQUIRE(AreEqualColors(shape.GetColor(), color));
				REQUIRE(AreEqualPoints(shape.GetCenter(), center));
				REQUIRE(shape.GetRadius() == 12);
				REQUIRE(shape.GetPointsCount() == 4);
			}
		}
	}
}

TEST_CASE("check test canvas")
{
	TestCanvas testCanvas;
	CPictureDraft pictureDraft;

	WHEN("add regular polygon and draw")
	{
		CPainter painter;

		CRegularPolygon regularPolygon(CColor(), {12, 12}, 4, 12);
		auto regularPolygonPtr = std::make_unique<CRegularPolygon>(regularPolygon);
		pictureDraft.AddShape(std::move(regularPolygonPtr));

		painter.DrawPicture(pictureDraft, testCanvas);

		THEN("in canvas will be regular polygon for drawing")
		{
			REQUIRE(testCanvas.GetResult() == std::vector<std::string>{"set color", "draw line", "draw line", "draw line", "draw line", "draw line"});
		}
	}

	WHEN("add rectangle and draw")
	{
		CPainter painter;

		CRectangle rectangle(CColor(), {12, 12}, 12, 12);
		auto rectanglePtr = std::make_unique<CRectangle>(rectangle);
		pictureDraft.AddShape(std::move(rectanglePtr));

		painter.DrawPicture(pictureDraft, testCanvas);

		THEN("in canvas will be rectangle for drawing")
		{
			REQUIRE(testCanvas.GetResult() == std::vector<std::string>{"set color", "draw line", "draw line", "draw line", "draw line"});
		}
	}

	WHEN("add ellipse and draw")
	{
		CPainter painter;

		CEllipse ellipse(CColor(), {12, 12}, 5, 12);
		auto ellipsePtr = std::make_unique<CEllipse>(ellipse);
		pictureDraft.AddShape(std::move(ellipsePtr));

		painter.DrawPicture(pictureDraft, testCanvas);

		THEN("in canvas will be ellipse commands for drawing")
		{
			REQUIRE(testCanvas.GetResult() == std::vector<std::string>{"set color", "draw ellipse"});
		}
	}

	WHEN("add triangle and draw")
	{
		CPainter painter;

		CTriangle triangle(CColor(), { 0, 0 }, { 10, 10 }, { 50, 50 });
		auto trianglePtr = std::make_unique<CTriangle>(triangle);

		pictureDraft.AddShape(std::move(trianglePtr));

		painter.DrawPicture(pictureDraft, testCanvas);

		THEN("in canvas will be ellipse commands for drawing")
		{
			REQUIRE(testCanvas.GetResult() == std::vector<std::string>{"set color", "draw line", "draw line", "draw line"});
		}
	}

	WHEN("add ellipse, regular polygon and draw")
	{
		CPainter painter;

		CEllipse ellipse(CColor(), {12, 12}, 5, 12);
		auto ellipsePtr = std::make_unique<CEllipse>(ellipse);
		pictureDraft.AddShape(std::move(ellipsePtr));

		CRegularPolygon regularPolygon(CColor(), {12, 12}, 4, 12);
		auto regularPolygonPtr = std::make_unique<CRegularPolygon>(regularPolygon);
		pictureDraft.AddShape(std::move(regularPolygonPtr));

		painter.DrawPicture(pictureDraft, testCanvas);

		THEN("in canvas will be ellipse commands for drawing")
		{
			REQUIRE(testCanvas.GetResult() == std::vector<std::string>{"set color", "draw ellipse", "set color", "draw line", "draw line", "draw line", "draw line", "draw line"});
		}
	}
}

TEST_CASE("test designer")
{
	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);

	std::string blueStr = "#0000ff";

	std::stringstream ss;
	ss << "rectangle #ff0000 5 4 2 1" << std::endl << "ellipse #0000ff 50 50 20 20";

	CPictureDraft pictureDraft = designer.CreateDraft(ss);

	REQUIRE(pictureDraft.GetShapesCount() == 2);
	auto testEllipse = dynamic_cast<CEllipse&>(pictureDraft.GetShape(1));

	REQUIRE(AreEqualColors(testEllipse.GetColor(), CColor(blueStr)));
	REQUIRE(AreEqualPoints(testEllipse.GetCenter(), {50, 50}));
	REQUIRE(testEllipse.GetHorizontalRadius() == 20);
	REQUIRE(testEllipse.GetVerticalRadius() == 20);
}

TEST_CASE("test painter functionality")
{
	GIVEN("picture draft and test canvas")
	{
		CPainter painter;

		CPictureDraft pictureDraft;
		TestCanvas testCanvas;

		CEllipse ellipse(CColor(), {12, 12}, 5, 12);
		auto ellipsePtr = std::make_unique<CEllipse>(ellipse);
		pictureDraft.AddShape(std::move(ellipsePtr));

		CRegularPolygon regularPolygon(CColor(), {12, 12}, 4, 12);
		auto regularPolygonPtr = std::make_unique<CRegularPolygon>(regularPolygon);
		pictureDraft.AddShape(std::move(regularPolygonPtr));

		WHEN("draw figures via painter")
		{
			REQUIRE_NOTHROW(painter.DrawPicture(pictureDraft, testCanvas));

			THEN("figures will be on the test canvas")
			{
				REQUIRE(testCanvas.GetResult() == std::vector<std::string>{"set color", "draw ellipse", "set color", "draw line", "draw line", "draw line", "draw line", "draw line"});
			}
		}
	}
}

TEST_CASE("test factory functionality")
{
	CShapeFactory shapeFactory;

	SECTION("check throwing exceptions")
	{
		REQUIRE_THROWS(shapeFactory.CreateShape(""));
		REQUIRE_THROWS(shapeFactory.CreateShape("triangke"));
		REQUIRE_THROWS(shapeFactory.CreateShape("triangle 10 20 15 00 30 40"));
	}

	SECTION("create ellipse")
	{
		auto shape = shapeFactory.CreateShape("ellipse #000000 12 12 12 12");

		CEllipse ellipse = dynamic_cast<CEllipse&>(*shape.get());

		REQUIRE(AreEqualColors(ellipse.GetColor(), CColor()));
		REQUIRE(AreEqualPoints(ellipse.GetCenter(), { 12, 12 }));
		REQUIRE(ellipse.GetHorizontalRadius() == 12);
		REQUIRE(ellipse.GetVerticalRadius() == 12);
	}

	SECTION("create rectangle")
	{
		std::string blueStr = "#0000ff";
		auto shape = shapeFactory.CreateShape("rectangle #0000ff 12 12 12 12");

		CRectangle rectangle = dynamic_cast<CRectangle&>(*shape.get());

		REQUIRE(AreEqualColors(rectangle.GetColor(), CColor(blueStr)));
		REQUIRE(AreEqualPoints(rectangle.GetLeftTop(), {12, 12}));
		REQUIRE(rectangle.GetWidth() == 12);
		REQUIRE(rectangle.GetHeight() == 12);
	}

	SECTION("create triangle")
	{
		auto shape = shapeFactory.CreateShape("triangle #000000 12 12 12 12 12 12");

		CTriangle triangle = dynamic_cast<CTriangle&>(*shape.get());

		REQUIRE(AreEqualColors(triangle.GetColor(), CColor()));
		REQUIRE(AreEqualPoints(triangle.GetVertex1(), {12, 12}));
		REQUIRE(AreEqualPoints(triangle.GetVertex2(), {12, 12}));
		REQUIRE(AreEqualPoints(triangle.GetVertex3(), {12, 12}));
	}

	SECTION("create regular polygon")
	{
		auto shape = shapeFactory.CreateShape("regularPolygon #000000 12 12 12 12");

		CRegularPolygon regularPolygon = dynamic_cast<CRegularPolygon&>(*shape.get());

		REQUIRE(AreEqualColors(regularPolygon.GetColor(), CColor()));
		REQUIRE(AreEqualPoints(regularPolygon.GetCenter(), {12, 12}));
		REQUIRE(regularPolygon.GetRadius() == 12);
		REQUIRE(regularPolygon.GetPointsCount() == 12);
	}
}
