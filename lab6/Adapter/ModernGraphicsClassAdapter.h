#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

class ModernGraphicsClassAdapter : public graphics_lib::ICanvas, public modern_graphics_lib::CModernGraphicsRenderer
{
public:
	explicit ModernGraphicsClassAdapter(std::ostream& strm)
		: CModernGraphicsRenderer(strm),
		m_start(0, 0)
	{}

	void SetColor(const uint32_t color) override
	{
		m_color = color;
	}

	void MoveTo(const int x, const int y) override
	{
		m_start = { x, y };
	}

	void LineTo(const int x, const int y) override
	{
		Point end(x, y);

		DrawLine(m_start, end, ConvertToColor(m_color));

		m_start.x = end.x;
		m_start.y = end.y;
	}

private:
	uint32_t m_color {};

	Point m_start;

	static modern_graphics_lib::CRGBAColor ConvertToColor(const uint32_t colorValue)
	{
		constexpr float colorScale = 1.0f / 255.0f;

		const auto red = static_cast<float>((colorValue >> 16) & 0xFF) * colorScale;
		const auto green = static_cast<float>((colorValue >> 8) & 0xFF) * colorScale;
		const auto blue = static_cast<float>(colorValue & 0xFF) * colorScale;
		const auto alpha = static_cast<float>((colorValue >> 24) & 0xFF) * colorScale;

		return { red, green, blue, alpha };
	}
};