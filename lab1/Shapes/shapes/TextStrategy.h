#pragma once
#pragma once
#include "../shapes/IShapeStrategy.h"
#include "../Point.h"

namespace shapes
{
	class TextStrategy : public IShapeStrategy
	{
	public:
		TextStrategy(Point point, double fontSize, std::string text)
			: m_topLeft(point),
			m_fontSize(fontSize),
			m_text(text)
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
				+ std::to_string(m_fontSize) + " "
				+ m_text;
		}

		std::string GetShapeType() const override
		{
			return "text";
		}

		void Draw(gfx::ICanvas& canvas) const override
		{
			canvas.DrawText(m_topLeft.m_x, m_topLeft.m_y, m_fontSize, m_text);
		}

	private:
		Point m_topLeft;
		double m_fontSize;
		std::string m_text;
	};
}