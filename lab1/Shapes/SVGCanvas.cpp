#include <iostream>
#include <fstream>
#include "SVGCanvas.h"

using namespace gfx;

constexpr int STROKE_WIDTH = 4;

SVGCanvas::SVGCanvas()
	: m_currentColor("#000000")
{
	m_outputSvg = std::stringstream("");
}

void SVGCanvas::Save(std::string const& outputFileName)
{
	std::ofstream outputFile(outputFileName);

	if (!outputFile.good())
	{
		throw std::invalid_argument("invalid output file");
	}

	outputFile << R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1">)" << std::endl;
	outputFile << m_outputSvg.str() << std::endl;
	outputFile << R"(</svg>)" << std::endl;
	outputFile.close();
}

void SVGCanvas::SetColor(const std::string& color)
{
	m_currentColor = color;
}

void SVGCanvas::MoveTo(double x, double y)
{
	m_drawPoint = { x, y };
}

void SVGCanvas::LineTo(double x, double y)
{
	std::string svgLine =
		R"(<line x1=")" + std::to_string(m_drawPoint.m_x) + R"(" )"
		+ R"(y1=")" + std::to_string(m_drawPoint.m_y) + R"(" )"
		+ R"(x2=")" + std::to_string(x) + R"(" )"
		+ R"(y2=")" + std::to_string(y) + R"(" )"
		+ R"(style="stroke:)" + m_currentColor
		+ R"(;stroke-width:)" + std::to_string(STROKE_WIDTH) + R"(" />)";
	m_outputSvg << svgLine << std::endl;
}

void SVGCanvas::DrawEllipse(double cx, double cy, double rx, double ry)
{
	std::string svgEllipse =
		R"(<ellipse cx=")" + std::to_string(cx) + R"(" )"
		+ R"(cy=")" + std::to_string(cy) + R"(" )"
		+ R"(rx=")" + std::to_string(rx) + R"(" )"
		+ R"(ry=")" + std::to_string(ry) + R"(" )"
		+ R"(style="stroke:)" + m_currentColor
		+ R"(;stroke-width:)" + std::to_string(STROKE_WIDTH) + R"(; fill:none;" />)";
	m_outputSvg << svgEllipse << std::endl;
}

void SVGCanvas::DrawText(double x, double y, double fontSize, std::string const& text)
{
	std::string svgText =
		R"(<text x=")" + std::to_string(x) + R"(" )"
		+ R"(y=")" + std::to_string(y) + R"(" )"
		+ R"(font-size=")" + std::to_string(fontSize) + R"(" )"
		+ R"(fill=")" + m_currentColor + R"(">)"
		+ text + R"(</text>)";
	m_outputSvg << svgText << std::endl;
}