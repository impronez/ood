#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

class ModernGraphicsAdapter : public graphics_lib::ICanvas
{
public:
	explicit ModernGraphicsAdapter(modern_graphics_lib::CModernGraphicsRenderer& modernRenderer)
		: m_start(0, 0),
		m_renderer(modernRenderer)
	{}

	void SetColor(const uint32_t color) override
	{
		m_color = color;
	}

	void MoveTo(int x, int y) override
	{
		m_start = { x, y };
	}

	void LineTo(const int x, const int y) override
	{
		Point end(x, y);

		m_renderer.DrawLine(m_start, end, ConvertToColor(m_color));

		m_start = end;
	}

private:
	uint32_t m_color {};

	Point m_start;

	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;

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