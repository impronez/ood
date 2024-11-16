#pragma once
#include <sstream>
#include <string>

#include "IShapeFactory.h"
#include "../Shape/CEllipse.h"
#include "../Shape/CRectangle.h"
#include "../Shape/CTriangle.h"

enum class ShapeType
{
    Ellipse,
    Rectangle,
    Triangle
};

class CShapeFactory : public IShapeFactory
{
public:
    std::shared_ptr<IShape> CreateShape(std::istringstream& params) override
    {
        std::string type;

        params >> type;
        auto shapeType = GetShapeTypeFromString(type);

        auto rect = GetShapeRectFromStringstream(params);
        auto lineStyle = GetStyleFromStringstream(params);
        auto fillStyle = GetStyleFromStringstream(params);

        switch (shapeType)
        {
            case ShapeType::Ellipse:
                return std::make_shared<CEllipse>(rect, lineStyle, fillStyle);
            case ShapeType::Rectangle:
                return std::make_shared<CRectangle>(rect, lineStyle, fillStyle);
            case ShapeType::Triangle:
                return std::make_shared<CTriangle>(rect, lineStyle, fillStyle);
            default:
                return nullptr;
        }
    }
private:
    static RectD GetShapeRectFromStringstream(std::istringstream &params)
    {
        double left, top, width, height;

        if (!(params >> left >> top >> width >> height))
        {
            throw std::invalid_argument("Invalid rect parameters");
        }

        if (width < 0 || height < 0)
        {
            throw std::invalid_argument("Width and height must be non-negative");
        }

        return { left, top, width, height };
    }

    static std::shared_ptr<IStyle> GetStyleFromStringstream(std::istringstream& params)
    {
        RGBAColor color {};

        if (!(params >> std::hex >> color))
        {
            throw std::invalid_argument("Invalid color");
        }

        auto style = std::make_shared<CStyle>();

        style->SetColor(color);
        style->Enable(true);

        return style;
    }

    static ShapeType GetShapeTypeFromString(std::string& type)
    {
        std::transform(type.begin(), type.end(), type.begin(),
                   [](unsigned char c) { return std::tolower(c); });

        if (type == "ellipse")
            return ShapeType::Ellipse;
        if (type == "rectangle")
            return ShapeType::Rectangle;
        if (type == "triangle")
            return ShapeType::Triangle;

        throw std::invalid_argument("Unknown shape type");
    }
};
