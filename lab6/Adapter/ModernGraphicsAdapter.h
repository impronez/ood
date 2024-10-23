#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

class ModernGraphicsAdapter : public graphics_lib::ICanvas
{
public:
	ModernGraphicsAdapter(modern_graphics_lib::CModernGraphicsRenderer& modernRenderer)
		: m_renderer(modernRenderer),
		m_startPoint(0, 0)
	{}

	void MoveTo(int x, int y) override
	{
		m_startPoint = { x, y };
	}

	void LineTo(int x, int y) override
	{
		const modern_graphics_lib::CPoint end(x, y);

		m_renderer.DrawLine(m_startPoint, end);

		m_startPoint = end;
	}

private:
	modern_graphics_lib::CPoint m_startPoint;
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
};