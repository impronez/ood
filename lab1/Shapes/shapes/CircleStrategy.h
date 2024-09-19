#pragma once
#include "IShapeStrategy.h"
#include "../Point.h"

namespace shapes
{
	class CircleStrategy : public IShapeStrategy
	{
	public:
		CircleStrategy(Point point, double radius)
			: m_center(point),
			m_radius(radius)
		{}

		void Move(double dx, double dy) override
		{
			m_center.m_x += dx;
			m_center.m_y += dy;
		}

		std::string GetShapeInfo() const override
		{
			return std::to_string(m_center.m_x) + " "
				+ std::to_string(m_center.m_y) + " "
				+ std::to_string(m_radius);
		}

		std::string GetShapeType() const override
		{
			return "circle";
		}

		void Draw(gfx::ICanvas& canvas) const override
		{
			canvas.DrawEllipse(m_center.m_x, m_center.m_y, m_radius, m_radius);
		}

	private:
		Point m_center;
		double m_radius;
	};
}