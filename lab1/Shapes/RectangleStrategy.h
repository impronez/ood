#pragma once
#include "IShapeStrategy.h"
#include "Point.h"

namespace shapes
{
	class RectangleStrategy : public IShapeStrategy
	{
	public:
		RectangleStrategy(Point point, double width, double height)
			: m_topLeft(point),
			m_width(width),
			m_height(height)
		{}

		void Move(double dx, double dy) override
		{
			m_topLeft.m_x += dx;
			m_topLeft.m_y += dy;
		}

		std::string GetShapeInfo() const override
		{
			return std::to_string(m_topLeft.m_x) + " "
				+ std::to_string(m_topLeft.m_y) + " "
				+ std::to_string(m_width) + " "
				+ std::to_string(m_height);
		}

		std::string GetShapeType() const override
		{
			return "rectangle";
		}

		void Draw(gfx::ICanvas& canvas) const override
		{
			canvas.MoveTo(m_topLeft.m_x, m_topLeft.m_y);
			canvas.LineTo(m_topLeft.m_x, m_topLeft.m_y + m_height);
			canvas.LineTo(m_topLeft.m_x + m_width, m_topLeft.m_y);

			canvas.MoveTo(m_topLeft.m_x + m_width, m_topLeft.m_y + m_height);
			canvas.LineTo(m_topLeft.m_x, m_topLeft.m_y + m_height);
			canvas.LineTo(m_topLeft.m_x + m_width, m_topLeft.m_y);
		}

	private:
		Point m_topLeft;
		double m_height;
		double m_width;
	};
}