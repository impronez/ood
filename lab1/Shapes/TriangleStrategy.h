#pragma once
#include "IShapeStrategy.h"
#include "Point.h"

namespace shapes
{
	class TriangleStrategy : public IShapeStrategy
	{
	public:
		TriangleStrategy(Point vertex1, Point vertex2, Point vertex3)
			: m_vertex1(vertex1),
			m_vertex2(vertex2),
			m_vertex3(vertex3)
		{}

		void Move(double dx, double dy) override
		{
			m_vertex1.m_x += dx;
			m_vertex1.m_y += dy;

			m_vertex2.m_x += dx;
			m_vertex2.m_y += dy;

			m_vertex3.m_x += dx;
			m_vertex3.m_y += dy;
		}
		std::string GetShapeInfo() const override
		{
			return std::to_string(m_vertex1.m_x) + " "
				+ std::to_string(m_vertex1.m_y) + " "
				+ std::to_string(m_vertex2.m_x) + " "
				+ std::to_string(m_vertex2.m_y) + " "
				+ std::to_string(m_vertex3.m_x) + " "
				+ std::to_string(m_vertex3.m_y);
		}

		std::string GetShapeType() const override
		{
			return "triangle";
		}

		void Draw(gfx::ICanvas& canvas) const override
		{
			canvas.MoveTo(m_vertex1.m_x, m_vertex1.m_y);
			canvas.LineTo(m_vertex2.m_x, m_vertex2.m_y);

			canvas.MoveTo(m_vertex2.m_x, m_vertex2.m_y);
			canvas.LineTo(m_vertex3.m_x, m_vertex3.m_y);

			canvas.MoveTo(m_vertex3.m_x, m_vertex3.m_y);
			canvas.LineTo(m_vertex1.m_x, m_vertex1.m_y);
		}

	private:
		Point m_vertex1;
		Point m_vertex2;
		Point m_vertex3;
	};
}