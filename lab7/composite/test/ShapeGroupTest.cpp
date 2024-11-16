#include <gtest/gtest.h>

#include "../Canvas/SVGCanvas.h"
#include "../Group/CShapeGroup.h"
#include "../Shape/CEllipse.h"
#include "../Shape/CRectangle.h"
#include "../Shape/CTriangle.h"

std::shared_ptr<CTriangle> GetTriangle(const RGBAColor lineColor, const bool isLineColorEnabled,
    const RGBAColor fillColor, const bool isFillColorEnabled)
{
    auto rect = RectD(0, 0, 10, 10);

    auto lineStyle = std::make_shared<CStyle>();
    lineStyle->SetColor(lineColor);
    lineStyle->Enable(isLineColorEnabled);

    auto fillStyle = std::make_shared<CStyle>();
    fillStyle->SetColor(fillColor);
    fillStyle->Enable(isFillColorEnabled);

    return std::make_shared<CTriangle>(rect, lineStyle, fillStyle);
}

std::shared_ptr<CRectangle> GetRectangle(const RGBAColor lineColor, const bool isLineColorEnabled,
    const RGBAColor fillColor, const bool isFillColorEnabled)
{
    auto rect = RectD(500, 450, 300, 200);

    auto lineStyle = std::make_shared<CStyle>();
    lineStyle->SetColor(lineColor);
    lineStyle->Enable(isLineColorEnabled);

    auto fillStyle = std::make_shared<CStyle>();
    fillStyle->SetColor(fillColor);
    fillStyle->Enable(isFillColorEnabled);

    return std::make_shared<CRectangle>(rect, lineStyle, fillStyle);
}

std::shared_ptr<CTriangle> GetEllipse(const RGBAColor lineColor, const bool isLineColorEnabled,
    const RGBAColor fillColor, const bool isFillColorEnabled)
{
    auto rect = RectD(345, 236, 150, 150);

    auto lineStyle = std::make_shared<CStyle>();
    lineStyle->SetColor(lineColor);
    lineStyle->Enable(isLineColorEnabled);

    auto fillStyle = std::make_shared<CStyle>();
    fillStyle->SetColor(fillColor);
    fillStyle->Enable(isFillColorEnabled);

    return std::make_shared<CTriangle>(rect, lineStyle, fillStyle);
}

std::shared_ptr<CShapeGroup> GetShapeGroupWithEqualStyles()
{
    auto triangle = GetTriangle(0xFF000000, true, 0xFF00FFFF, true);
    auto rectangle = GetRectangle(0xFF000000, true, 0xFF00FFFF, true);
    auto ellipse = GetEllipse(0xFF000000, true, 0xFF00FFFF, true);

    std::vector<std::shared_ptr<IShape>> shapes = { triangle, rectangle, ellipse };
    auto shapeGroup = std::make_shared<CShapeGroup>(shapes);

    return shapeGroup;
}

std::shared_ptr<CShapeGroup> GetShapeGroupWithDifferentStyles()
{

    auto rectangle = GetRectangle(0xFF000000, true, 0xFF00FFFF, true);
    auto ellipse = GetEllipse(0xFF00FFFF, true, 0xFF00FF00, true);
    auto triangle = GetTriangle(0xFF0000FF, true, 0xFF010FF0, true);

    std::vector<std::shared_ptr<IShape>> shapes = { triangle, rectangle, ellipse };

    auto shapeGroup = std::make_shared<CShapeGroup>(shapes);

    return shapeGroup;
}

bool AreEqualLineStyles(const std::shared_ptr<IStyle>& style1, const std::shared_ptr<IStyle>& style2)
{
    return style1->GetColor() == style2->GetColor();
}

bool AreEqualFrames(const RectD& rect1, const RectD& rect2)
{
    return rect1.left == rect2.left
        && rect1.top == rect2.top
        && rect1.width == rect2.width
        && rect1.height == rect2.height;
}

class TestCanvas final : public ICanvas
{
public:
    void SetLineColor(RGBAColor color) override {}
    void SetStrokeWidth(unsigned strokeWidth) override {}
    void BeginFill(RGBAColor color) override {}
    void EndFill() override {}
    void MoveTo(double x, double y) override {}
    void LineTo(double x, double y) override {}
    void DrawEllipse(double left, double top, double width, double height) override
    {
        count++;
    }
    void Export(std::ostream &output) override {}

    size_t count = 0;
};

TEST(CShapeGroup, Constructor)
{
    std::vector<std::shared_ptr<IShape>> emptyShapes;
    EXPECT_THROW(auto group = CShapeGroup(emptyShapes) , std::invalid_argument);

    auto triangle = GetTriangle(0xFF000000, true, 0xFF00FFFF, true);
    EXPECT_NO_THROW(auto group = CShapeGroup(triangle));

    std::vector<std::shared_ptr<IShape>> shapes = { triangle };
    EXPECT_NO_THROW(auto group = CShapeGroup(shapes));

    auto group = CShapeGroup(triangle);
    EXPECT_EQ(group.GetShapesCount(), 1);

    group = CShapeGroup(shapes);
    EXPECT_EQ(group.GetShapesCount(), 1);
}

TEST(CShapeGroup, GetLineStyleMethod)
{
    auto shapeGroupWithoutShapes = std::make_shared<CShapeGroup>(GetRectangle(0xFF000000, true, 0xFF00FFFF, true));
    shapeGroupWithoutShapes->RemoveShapeAtIndex(0);
    EXPECT_EQ(shapeGroupWithoutShapes->GetLineStyle(), nullptr);

    auto shapeGroupWithDifferentShapes = GetShapeGroupWithDifferentStyles();
    EXPECT_EQ(shapeGroupWithDifferentShapes->GetLineStyle(), nullptr);

    auto shapeGroupWithEqualShapes = GetShapeGroupWithEqualStyles();
    EXPECT_EQ(AreEqualLineStyles(shapeGroupWithEqualShapes->GetLineStyle(),
        shapeGroupWithEqualShapes->GetShapeAtIndex(0)->GetLineStyle()), true);

    auto triangle = GetTriangle(0xFF0000F0, true, 0xFF00FFFF, true);
    auto rectangle = GetRectangle(0xFF0F0000, true, 0xFF00FFFF, true);
    auto group = CShapeGroup(triangle);
    group.InsertShape(rectangle);

    EXPECT_EQ(group.GetLineStyle(), nullptr);
}

TEST(CShapeGroup, GetFillStyleMethod)
{
    auto shapeGroupWithoutShapes = std::make_shared<CShapeGroup>(GetRectangle(0xFF000000, true, 0xFF00FFFF, true));
    shapeGroupWithoutShapes->RemoveShapeAtIndex(0);
    EXPECT_EQ(shapeGroupWithoutShapes->GetFillStyle(), nullptr);

    auto shapeGroupWithDifferentShapes = GetShapeGroupWithDifferentStyles();
    EXPECT_EQ(shapeGroupWithDifferentShapes->GetFillStyle(), nullptr);

    auto shapeGroupWithEqualShapes = GetShapeGroupWithEqualStyles();
    EXPECT_EQ(AreEqualLineStyles(shapeGroupWithEqualShapes->GetFillStyle(),
        shapeGroupWithEqualShapes->GetShapeAtIndex(0)->GetFillStyle()), true);

    auto triangle = GetTriangle(0xFF0000F0, true, 0xFF00FFFF, true);
    auto rectangle = GetRectangle(0xFF0F0000, true, 0xFF00F0FF, true);
    auto group = CShapeGroup(triangle);
    group.InsertShape(rectangle);

    EXPECT_EQ(group.GetFillStyle(), nullptr);
}

TEST(CShapeGroup, SetLineStyleMethod)
{
    auto triangle = GetTriangle(0xFFAABBCD, true, 0xFF00FFFF, true);
    auto group = CShapeGroup(triangle);

    group.SetLineStyle(0xFDABCDEF, false);

    EXPECT_EQ(group.GetLineStyle()->GetColor(), 0xFDABCDEF);
    EXPECT_EQ(group.GetLineStyle()->IsEnabled(), false);
}

TEST(CShapeGroup, SetFillStyleMethod)
{
    auto triangle = GetTriangle(0xFFAABBCD, true, 0xFF00FFFF, true);
    auto group = CShapeGroup(triangle);

    group.SetFillStyle(0xFDABCDEF, false);

    EXPECT_EQ(group.GetFillStyle()->GetColor(), 0xFDABCDEF);
    EXPECT_EQ(group.GetFillStyle()->IsEnabled(), false);
}

TEST(CShapeGroup, GetShapeGroup)
{
    auto group = GetShapeGroupWithDifferentStyles();

    EXPECT_EQ(group->GetShapeGroup(), group);
}

TEST(CShapeGroup, GetFrameMethod)
{
    auto ellipse1 = std::make_shared<CEllipse>(
        RectD(100, 50, 200, 550),
        std::make_shared<CStyle>(),
        std::make_shared<CStyle>()
    );

    auto shapeGroup = std::make_shared<CShapeGroup>(ellipse1);

    auto ellipse2 = std::make_shared<CEllipse>(
        RectD(300, 10, 600, 200),
        std::make_shared<CStyle>(),
        std::make_shared<CStyle>()
    );

    shapeGroup->InsertShape(ellipse2);

    RectD resultFrame = { 100, 10, 800, 590 };
    RectD shapeGroupFrame = shapeGroup->GetFrame().value();

    EXPECT_EQ(AreEqualFrames(shapeGroupFrame, resultFrame), true);

    shapeGroup->RemoveShapeAtIndex(0);
    shapeGroup->RemoveShapeAtIndex(0);

    std::optional<RectD> frame = shapeGroup->GetFrame();
    EXPECT_EQ(frame.has_value(), false);
}

TEST(CShapeGroup, SetFrameMethod)
{
    auto ellipse = std::make_shared<CEllipse>(
        RectD(300, 10, 600, 200),
        std::make_shared<CStyle>(),
        std::make_shared<CStyle>()
    );

    auto shapeGroup = std::make_shared<CShapeGroup>(ellipse);

    shapeGroup->SetFrame(100, 150, 400, 500);
    auto resultFrame = RectD(100, 150, 400, 500);
    EXPECT_EQ(AreEqualFrames(shapeGroup->GetFrame().value(), resultFrame), true);

    shapeGroup->RemoveShapeAtIndex(0);
    shapeGroup->SetFrame(100, 100, 100, 100);

    auto frame = shapeGroup->GetFrame();
    EXPECT_EQ(frame.has_value(), false);
}

TEST(CShapeGroup, DrawMethod)
{
    TestCanvas canvas;

    auto ellipse1 = std::make_shared<CEllipse>(
        RectD(100, 100, 200, 200),
        std::make_shared<CStyle>(),
        std::make_shared<CStyle>()
    );

    auto ellipse2 = std::make_shared<CEllipse>(
        RectD(150, 150, 200, 200),
        std::make_shared<CStyle>(),
        std::make_shared<CStyle>()
    );

    auto shapeGroup = std::make_shared<CShapeGroup>(ellipse1);
    shapeGroup->InsertShape(ellipse2);

    shapeGroup->Draw(canvas);

    EXPECT_EQ(canvas.count, 2);
}

TEST(CShapeGroup, GetShapesCountMethod)
{
    auto rectangle = GetRectangle(0xFFAABBCD, true, 0xFF00FFFF, true);

    auto group = CShapeGroup(rectangle);
    group.RemoveShapeAtIndex(0);

    EXPECT_EQ(group.GetShapesCount(), 0);

    auto ellipse = std::make_shared<CEllipse>(
        RectD(150, 150, 200, 200),
        std::make_shared<CStyle>(),
        std::make_shared<CStyle>()
    );
    auto shapeGroup = std::make_shared<CShapeGroup>(ellipse);

    EXPECT_EQ(shapeGroup->GetShapesCount(), 1);
}

TEST(CShapeGroup, InsertShapeMethod)
{
    auto ellipse1 = std::make_shared<CEllipse>(
        RectD(150, 150, 200, 200),
        std::make_shared<CStyle>(),
        std::make_shared<CStyle>()
    );

    auto shapeGroup = std::make_shared<CShapeGroup>(ellipse1);

    EXPECT_EQ(shapeGroup->GetShapesCount(), 1);

    auto ellipse2 = std::make_shared<CEllipse>(
        RectD(150, 150, 200, 200),
        std::make_shared<CStyle>(),
        std::make_shared<CStyle>()
    );

    auto ellipse3 = std::make_shared<CEllipse>(
        RectD(150, 150, 200, 200),
        std::make_shared<CStyle>(),
        std::make_shared<CStyle>()
    );

    shapeGroup->InsertShape(ellipse2, 0);
    shapeGroup->InsertShape(ellipse3, 1);
    EXPECT_EQ(shapeGroup->GetShapesCount(), 3);
    EXPECT_EQ(shapeGroup->GetShapeAtIndex(0), ellipse2);
    EXPECT_EQ(shapeGroup->GetShapeAtIndex(1), ellipse3);
}

TEST(CShapeGroup, GetShapeAtIndexMethod)
{

    auto ellipse = std::make_shared<CEllipse>(
        RectD(150, 150, 200, 200),
        std::make_shared<CStyle>(),
        std::make_shared<CStyle>()
    );

    auto shapeGroup = std::make_shared<CShapeGroup>(ellipse);

    EXPECT_EQ(shapeGroup->GetShapeAtIndex(0), ellipse);
    EXPECT_THROW(shapeGroup->GetShapeAtIndex(10), std::out_of_range);
}

TEST(CShapeGroup, RemoveShapeAtIndexMethod)
{
    auto ellipse = std::make_shared<CEllipse>(
        RectD(150, 150, 200, 200),
        std::make_shared<CStyle>(),
        std::make_shared<CStyle>()
    );

    auto shapeGroup = std::make_shared<CShapeGroup>(ellipse);

    EXPECT_THROW(shapeGroup->RemoveShapeAtIndex(5), std::out_of_range);

    shapeGroup->RemoveShapeAtIndex(0);
    EXPECT_EQ(shapeGroup->GetShapesCount(), 0);
}

TEST(CShapeGroup, GetType)
{
    auto ellipse = GetEllipse(0xFF000000, true, 0xFF00FF00, true);
    auto shapeGroup = std::make_shared<CShapeGroup>(ellipse);

    EXPECT_EQ(shapeGroup->GetType(), CShapeGroup::TYPE);
}