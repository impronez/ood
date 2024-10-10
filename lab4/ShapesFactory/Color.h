#pragma once
#include <string>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <map>

namespace
{
	enum class Color
	{
		Red,
		Green,
		Blue,
		Pink,
		Yellow,
		Black
	};

	const std::map<Color, std::string> COLOR_TO_HEX =
	{
		{ Color::Red, "#ff0000" },
		{ Color::Green, "#00ff00" },
		{ Color::Blue, "#0000ff" },
		{ Color::Pink, "#ffc0cb" },
		{ Color::Yellow, "#ffff00" },
		{ Color::Black, "#000000" },
	};

	static const std::map<std::string, Color> HEX_TO_COLOR =
	{
		{ "#ff0000", Color::Red },
		{ "#00ff00", Color::Green },
		{ "#0000ff", Color::Blue },
		{ "#ffc0cb", Color::Pink },
		{ "#ffff00", Color::Yellow },
		{ "#000000", Color::Black },
	};
}

class CColor
{
public:
	CColor()
		: m_color(Color::Black)
	{}

	CColor(std::string& colorStr)
	{
		m_color = GetHexFromColor(colorStr);
	}

	std::string GetStringView() const
	{
		if (!COLOR_TO_HEX.contains(m_color))
		{
			throw std::invalid_argument("Invalid color");
		}

		return COLOR_TO_HEX.at(m_color);
	}
private:
	Color GetHexFromColor(std::string& colorStr)
	{
		std::transform(colorStr.begin(), colorStr.end(), colorStr.begin(),
			[](unsigned char c) { return std::tolower(c); });

		if (!HEX_TO_COLOR.contains(colorStr))
		{
			throw std::invalid_argument("Invalid color");
		}

		return HEX_TO_COLOR.at(colorStr);
	}

	Color m_color;
};