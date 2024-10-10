#pragma once
#include "IShapeFactory.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CRegularPolygon.h"
#include <sstream>
#include <map>

enum class ShapeType
{
    Rectangle,
    Triangle,
    Ellipse,
    RegularPolygon
};

class CShapeFactory : public IShapeFactory
{
public:
    std::unique_ptr<CShape> CreateShape(const std::string& description) override;

private:
    static std::unique_ptr<CTriangle> CreateTriangle(CColor& color, std::istringstream& params);

    static std::unique_ptr<CRectangle> CreateRectangle(CColor& color, std::istringstream& params);

    static std::unique_ptr<CEllipse> CreateEllipse(CColor& color, std::istringstream& params);

    static std::unique_ptr<CRegularPolygon> CreateRegularPolygon(CColor& color, std::istringstream& params);

    static std::map<std::string, ShapeType> s_mapShapeTypes;
};