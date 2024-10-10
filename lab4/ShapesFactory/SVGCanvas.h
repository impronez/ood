#pragma once
#include "ICanvas.h"
#include <string>
#include <sstream>
#include <fstream>

class SVGCanvas : public ICanvas
{
public:
	explicit SVGCanvas()
		: m_currentColor(CColor())
	{}

	void SetColor(const CColor color) override
	{
		m_currentColor = color;
	}

	void DrawLine(double fromX, double fromY, double toX, double toY) override
	{
		std::string svgLine =
			R"(<line x1=")" + std::to_string(fromX) + R"(" )"
			+ R"(y1=")" + std::to_string(fromY) + R"(" )"
			+ R"(x2=")" + std::to_string(toX) + R"(" )"
			+ R"(y2=")" + std::to_string(toY) + R"(" )"
			+ R"(style="stroke:)" + m_currentColor.GetStringView()
			+ R"(;stroke-width:)" + std::to_string(s_strokeWidth) + R"(" />)";
		m_outputSvg << svgLine << std::endl;
	}

	void DrawEllipse(double cx, double cy, double rx, double ry) override
	{
		std::string svgEllipse =
			R"(<ellipse cx=")" + std::to_string(cx) + R"(" )"
			+ R"(cy=")" + std::to_string(cy) + R"(" )"
			+ R"(rx=")" + std::to_string(rx) + R"(" )"
			+ R"(ry=")" + std::to_string(ry) + R"(" )"
			+ R"(style="stroke:)" + m_currentColor.GetStringView()
			+ R"(;stroke-width:)" + std::to_string(s_strokeWidth) + R"(; fill:none;" />)";
		m_outputSvg << svgEllipse << std::endl;
	}

	void Save(std::string const& outputFileName)
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
private:
	CColor m_currentColor;
	std::stringstream m_outputSvg;

	static const int s_strokeWidth = 4;
};