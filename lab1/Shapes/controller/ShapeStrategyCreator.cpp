#include "ShapeStrategyCreator.h"

using namespace shapes;

std::map<std::string, ShapeType> ShapeStrategyCreator::s_mapShapeTypes =
{
	{ "circle", ShapeType::CIRCLE },
	{ "line", ShapeType::LINE },
	{ "text", ShapeType::TEXT },
	{ "triangle", ShapeType::TRIANGLE },
	{ "rectangle", ShapeType::RECTANGLE }
};

std::unique_ptr<IShapeStrategy> ShapeStrategyCreator::CreateFromStream(std::istream& input)
{
	std::string type;
	input >> type;

	if (!s_mapShapeTypes.contains(type))
	{
		auto msg = "Unknown shape type: " + type;
		throw std::exception(msg.c_str());
	}

	ShapeType shape = s_mapShapeTypes.at(type);

	switch (shape)
	{
	case ShapeType::CIRCLE:
		return std::make_unique<CircleStrategy>(CreateCircleStrategy(input));
	case ShapeType::LINE:
		return std::make_unique<LineStrategy>(CreateLineStrategy(input));
	case ShapeType::RECTANGLE:
		return std::make_unique<RectangleStrategy>(CreateRectangleStrategy(input));
	case ShapeType::TEXT:
		return std::make_unique<TextStrategy>(CreateTextStrategy(input));
	case ShapeType::TRIANGLE:
		return std::make_unique<TriangleStrategy>(CreateTriangleStrategy(input));
	default:
		break;
	}

	throw std::exception("Unknown shape");
}

CircleStrategy ShapeStrategyCreator::CreateCircleStrategy(std::istream& input)
{
	std::string cxStr, cyStr, rStr;

	input >> cxStr >> cyStr >> rStr;

	if (cxStr.empty() || cyStr.empty() || rStr.empty())
	{
		throw std::exception("Invalid circle arguments, use: <center x> <center y> <radius>");
	}

	try
	{
		double cx = stod(cxStr);
		double cy = stod(cyStr);
		double r = stod(rStr);

		return CircleStrategy(Point{ cx, cy }, r);
	}
	catch (...)
	{
		throw std::exception("incorrect circle params");
	}
}

LineStrategy ShapeStrategyCreator::CreateLineStrategy(std::istream& input)
{
	std::string x1Str, y1Str, x2Str, y2Str;

	input >> x1Str >> y1Str >> x2Str >> y2Str;

	if (x1Str.empty() || y1Str.empty() || x2Str.empty() || y2Str.empty())
	{
		throw std::exception("Invalid line arguments, use: <x1> <y1> <x2> <y2>");
	}

	try
	{
		double x1 = stod(x1Str);
		double y1 = stod(y1Str);
		double x2 = stod(x2Str);
		double y2 = stod(y2Str);

		return LineStrategy(Point{ x1, y1 }, Point{ x2, y2 });
	}
	catch (...)
	{
		throw std::exception("Incorrect line params");
	}
}

TextStrategy ShapeStrategyCreator::CreateTextStrategy(std::istream& input)
{
	std::string xStr, yStr, fontSizeStr, text;

	input >> xStr >> yStr >> fontSizeStr;

	getline(input, text);

	if (xStr.empty() || yStr.empty() || fontSizeStr.empty() || text.empty())
	{
		throw std::exception("Invalid text arguments, use: <left> <top> <size> <text>");
	}

	try
	{
		double x = stod(xStr);
		double y = stod(yStr);
		double fontSize = stod(fontSizeStr);

		return TextStrategy(Point{ x, y }, fontSize, move(text));
	}
	catch (...)
	{
		throw std::exception("Incorrect text params");
	}
}

TriangleStrategy ShapeStrategyCreator::CreateTriangleStrategy(std::istream& input)
{
	std::string x1str, y1str, x2str, y2str, x3str, y3str;

	input >> x1str >> y1str >> x2str >> y2str >> x3str >> y3str;

	if (x1str.empty() || y1str.empty()
		|| x2str.empty() || y2str.empty()
		|| x3str.empty() || y3str.empty())
	{
		throw std::exception("Invalid triangle arguments, use: <x1> <y1> <x2> <y2> <x3> <y3>");
	}

	try
	{
		double x1 = stod(x1str), y1 = stod(y1str);
		double x2 = stod(x2str), y2 = stod(y2str);
		double x3 = stod(x3str), y3 = stod(y3str);

		return TriangleStrategy(Point{ x1, y1 }, Point{ x2, y2 }, Point{ x3, y3 });
	}
	catch (...)
	{
		throw std::exception("Incorrect triangle params");
	}
}

RectangleStrategy ShapeStrategyCreator::CreateRectangleStrategy(std::istream& input)
{
	std::string xStr, yStr, widthStr, heightStr;

	input >> xStr >> yStr >> widthStr >> heightStr;

	if (xStr.empty() || yStr.empty() || widthStr.empty() || heightStr.empty())
	{
		throw std::exception("Invalid rectangle arguments, use: <x1> <y1> <width> <height>");
	}

	try
	{
		double x = stod(xStr);
		double y = stod(yStr);

		double width = stod(widthStr);
		double height = stod(heightStr);

		return RectangleStrategy(Point{ x, y }, width, height);
	}
	catch (...)
	{
		throw std::exception("Incorrect text params");
	}
}
