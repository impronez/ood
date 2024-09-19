#pragma once
#include "../shapes/IShapeStrategy.h"
#include <memory>

namespace shapes
{
	class Shape
	{
	public:
		Shape(std::string id, const std::string& color, std::unique_ptr<shapes::IShapeStrategy> shapeStrategy)
			: m_id(id), m_color(color), m_shapeStrategy(move(shapeStrategy))
		{}

		void Draw(gfx::ICanvas& canvas) const
		{
			canvas.SetColor(m_color);
			m_shapeStrategy->Draw(canvas);
		}
		
		std::string GetColor() const
		{
			return m_color;
		}

		std::string GetShapeInfo() const
		{
			return m_shapeStrategy->GetShapeInfo();
		}

		std::string GetShapeType() const
		{
			return m_shapeStrategy->GetShapeType();
		}

		void SetColor(const std::string& color)
		{
			m_color = color;
		}

		void Move(double dx, double dy)
		{
			m_shapeStrategy->Move(dx, dy);
		}

		void SetShapeStrategy(std::unique_ptr<shapes::IShapeStrategy> strategy)
		{
			m_shapeStrategy = move(strategy);
		}

		std::string GetId() const
		{
			return m_id;
		}

	private:
		std::string m_id;
		std::string m_color;
		std::unique_ptr<shapes::IShapeStrategy> m_shapeStrategy;
	};
}

