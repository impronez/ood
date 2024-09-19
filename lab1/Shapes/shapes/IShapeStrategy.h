#pragma once
#include "../gfx/ICanvas.h"

namespace shapes
{
	class IShapeStrategy
	{
	public:
		virtual void Move(double dx, double dy) = 0;
		virtual std::string GetShapeInfo() const = 0;
		virtual std::string GetShapeType() const = 0;
		virtual void Draw(gfx::ICanvas& canvas) const = 0;
	};
}
