#pragma once
#include <iostream>
#include <map>
#include "IShapeStrategy.h"
#include "CircleStrategy.h"
#include "LineStrategy.h"
#include "TextStrategy.h"
#include "TriangleStrategy.h"
#include "RectangleStrategy.h"

namespace shapes
{
	enum class ShapeType
	{
		CIRCLE,
		LINE,
		TEXT,
		TRIANGLE,
		RECTANGLE,
	};

	class ShapeStrategyCreator
	{
	public:
		static std::unique_ptr<shapes::IShapeStrategy> CreateFromStream(std::istream& input);
	private:

		static CircleStrategy CreateCircleStrategy(std::istream& input);
		static LineStrategy CreateLineStrategy(std::istream& input);
		static TextStrategy CreateTextStrategy(std::istream& input);
		static TriangleStrategy CreateTriangleStrategy(std::istream& input);
		static RectangleStrategy CreateRectangleStrategy(std::istream& input);

		static std::map<std::string, ShapeType> s_mapShapeTypes;
	};
}