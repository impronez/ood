#pragma once
#include <string>

namespace gfx
{
	class ICanvas
	{
	public:
		virtual void MoveTo(double x, double y) = 0;
		virtual void SetColor(const std::string& color) = 0;
		virtual void LineTo(double x, double y) = 0;
		virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;
		virtual void DrawText(double x, double y, double fontSize, std::string const& text) = 0;

		virtual ~ICanvas() {};
	};
}