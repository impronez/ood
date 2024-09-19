#pragma once
#include <iostream>
#include <map>
#include "../shapes/IShapeStrategy.h"
#include "../shapes/CircleStrategy.h"
#include "../shapes/LineStrategy.h"
#include "../shapes/TextStrategy.h"
#include "../shapes/TriangleStrategy.h"
#include "../shapes/RectangleStrategy.h"

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