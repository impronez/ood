#pragma once
#include "Shape.h"
#include "IShapeStrategy.h"
#include "Color.h"
#include <map>
#include <vector>

namespace shapes
{
	class Picture
	{
	public:

		Picture() {}

		void AddShape(const std::string& id, const gfx::Color& color, std::unique_ptr<IShapeStrategy> strategy);

		void DeleteShape(std::string id);

		void MoveShape(const std::string& id, double dx, double dy);
		void MovePicture(double dx, double dy);

		void DrawShape(gfx::ICanvas& canvas, const std::string& id);
		void DrawPicture(gfx::ICanvas& canvas);

		std::vector<std::string> List() const;

		void ChangeColor(const std::string& id, const gfx::Color& color);
		void ChangeShape(const std::string& id, std::unique_ptr<shapes::IShapeStrategy> shapeStrategy);

		std::shared_ptr<Shape> GetShapeById(const std::string& id) const;

	private:
		std::map<std::string, std::shared_ptr<Shape>> m_shapes;
	};
}
