#include "CShapeFactory.h"

std::map<std::string, ShapeType> CShapeFactory::s_mapShapeTypes =
{
	{ "triangle", ShapeType::Triangle },
	{ "rectangle", ShapeType::Rectangle },
	{ "ellipse", ShapeType::Ellipse },
	{ "regularpolygon", ShapeType::RegularPolygon }
};

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string& description)
{
	std::istringstream iss(description);

	std::string shapeTypeStr;
	iss >> shapeTypeStr;
	std::transform(shapeTypeStr.begin(), shapeTypeStr.end(), shapeTypeStr.begin(),
		[](unsigned char c) { return std::tolower(c); });

	if (!s_mapShapeTypes.contains(shapeTypeStr))
	{
		auto msg = "Unknown shape type: " + shapeTypeStr;
		throw std::exception(msg.c_str());
	}

	ShapeType shapeType = s_mapShapeTypes.at(shapeTypeStr);

	std::string colorStr;
	iss >> colorStr;

	CColor color(colorStr);

	switch (shapeType)
	{
	case ShapeType::Rectangle:
		return CreateRectangle(color, iss);
	case ShapeType::Triangle:
		return CreateTriangle(color, iss);
	case ShapeType::Ellipse:
		return CreateEllipse(color, iss);
	case ShapeType::RegularPolygon:
		return CreateRegularPolygon(color, iss);
	default:
		throw std::invalid_argument("Unknown shape type: " + shapeTypeStr);
	}
}

std::unique_ptr<CTriangle> CShapeFactory::CreateTriangle(CColor& color, std::istringstream& params)
{
	std::string x1Str, y1Str,
		x2Str, y2Str,
		x3Str, y3Str;

	params >> x1Str >> y1Str >> x2Str >> y2Str >> x3Str >> y3Str;

	if (x1Str.empty() || x2Str.empty() || x3Str.empty()
		|| y1Str.empty() || y2Str.empty() || y3Str.empty())
	{
		throw std::exception("Invalid triangle arguments, use: <x1> <y1> <x2> <y2> <x3> <y3>");
	}

	try
	{
		Point p1(std::stod(x1Str), std::stod(y1Str));
		Point p2(std::stod(x2Str), std::stod(y2Str));
		Point p3(std::stod(x3Str), std::stod(y3Str));

		return std::make_unique<CTriangle>(color, p1, p2, p3);
	}
	catch (...)
	{
		throw std::exception("Incorrect triangle params");
	}
}

std::unique_ptr<CRectangle> CShapeFactory::CreateRectangle(CColor& color, std::istringstream& params)
{
	std::string leftStr, topStr, widthStr, heightStr;

	params >> leftStr >> topStr >> widthStr >> heightStr;

	if (leftStr.empty() || topStr.empty() || widthStr.empty()|| heightStr.empty())
	{
		throw std::exception("Invalid triangle arguments, use: <left> <top> <width> <height>");
	}

	try
	{
		Point leftTop(std::stod(leftStr), std::stod(topStr));

		double width = std::stod(widthStr);
		double height = std::stod(heightStr);

		return std::make_unique<CRectangle>(color, leftTop, width, height);
	}
	catch (...)
	{
		throw std::exception("Incorrect triangle params");
	}
}

std::unique_ptr<CEllipse> CShapeFactory::CreateEllipse(CColor& color, std::istringstream& params)
{
	std::string centerXStr, centerYStr;
	std::string horizontalRadiusStr, verticalRadiusStr;

	params >> centerXStr >> centerYStr >> horizontalRadiusStr >> verticalRadiusStr;

	if (centerXStr.empty() || centerYStr.empty()
		|| horizontalRadiusStr.empty() || verticalRadiusStr.empty())
	{
		throw std::exception("Invalid ellipse arguments, use: <centerX> <centerY> <horizontal radius> <vertical radius>");
	}

	try
	{
		Point center(std::stod(centerXStr), std::stod(centerYStr));

		double horizontalRadius = std::stod(horizontalRadiusStr);
		double verticalRadius = std::stod(verticalRadiusStr);

		return std::make_unique<CEllipse>(color, center, horizontalRadius, verticalRadius);
	}
	catch (...)
	{
		throw std::exception("Incorrect triangle params");
	}
}

std::unique_ptr<CRegularPolygon> CShapeFactory::CreateRegularPolygon(CColor& color, std::istringstream& params)
{
	std::string centerXStr, centerYStr;
	std::string verticesCountStr;
	std::string radiusStr;

	params >> centerXStr >> centerYStr >> verticesCountStr >> radiusStr;

	if (centerXStr.empty() || centerYStr.empty()
		|| verticesCountStr.empty() || radiusStr.empty())
	{
		throw std::exception("Invalid regular polygon arguments, use: <centerX> <centerY> <vertices count> <radius>");
	}

	try
	{
		Point center(std::stod(centerXStr), std::stod(centerYStr));

		int verticesCount = std::stoi(verticesCountStr);
		double radius = std::stod(radiusStr);

		return std::make_unique<CRegularPolygon>(color, center, verticesCount, radius);
	}
	catch (...)
	{
		throw std::exception("Incorrect triangle params");
	}
}
