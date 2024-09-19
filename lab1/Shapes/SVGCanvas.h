#pragma once
#include "ICanvas.h"
#include <sstream>
#include "Point.h"

class SVGCanvas : public gfx::ICanvas
{
public:
	explicit SVGCanvas();

	void SetColor(const std::string& color) override;
	void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double cx, double cy, double rx, double ry) override;
	void DrawText(double x, double y, double fontSize, std::string const& text) override;

	void Save(std::string const& outputFileName);
private:
	std::string m_currentColor;
	Point m_drawPoint;
	std::stringstream m_outputSvg;
};