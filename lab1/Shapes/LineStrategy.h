#pragma once
#include "IShapeStrategy.h"
#include "Point.h"

namespace shapes
{
	class LineStrategy : public IShapeStrategy
	{
	public:
		LineStrategy(Point startPoint, Point endPoint)
			: m_startPoint(startPoint),
			m_endPoint(endPoint)
		{}

		void Move(double dx, double dy) override
		{
			m_startPoint.m_x += dx;
			m_startPoint.m_y += dy;

			m_endPoint.m_x += dx;
			m_endPoint.m_y += dy;
		}

		std::string GetShapeInfo() const override
		{
			return std::to_string(m_startPoint.m_x) + " "
				+ std::to_string(m_startPoint.m_y) + " "
				+ std::to_string(m_endPoint.m_x) + " "
				+ std::to_string(m_endPoint.m_y);
		}

		std::string GetShapeType() const override
		{
			return "line";
		}

		void Draw(gfx::ICanvas& canvas) const override
		{
			canvas.MoveTo(m_startPoint.m_x, m_startPoint.m_y);
			canvas.LineTo(m_endPoint.m_x, m_endPoint.m_y);
		}

	private:
		Point m_startPoint;
		Point m_endPoint;
	};
}