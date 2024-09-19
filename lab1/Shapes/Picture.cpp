#include "Picture.h"
#include <algorithm>
#include <iostream>

using namespace shapes;

void shapes::Picture::AddShape(const std::string& id, const gfx::Color& color, std::unique_ptr<IShapeStrategy> strategy)
{
	if (m_shapes.contains(id))
	{
		throw std::invalid_argument("Shape with this id already exists");
	}

	auto shape = std::make_shared<Shape>(Shape(id, color, move(strategy)));

	m_shapes.insert({ id, shape });
}

void Picture::DeleteShape(std::string id)
{
	auto it = m_shapes.find(id);
	if (it == m_shapes.end())
	{
		throw std::invalid_argument("Shape with this id doesn't exist");
	}
	m_shapes.erase(it);
}

void Picture::MoveShape(const std::string& id, double dx, double dy)
{
	if (m_shapes.contains(id))
	{
		throw std::invalid_argument("Shape with this id already exists");
	}
	m_shapes.at(id)->Move(dx, dy);
}

void Picture::MovePicture(double dx, double dy)
{
	for (auto& shape : m_shapes)
	{
		shape.second->Move(dx, dy);
	}
}

void Picture::DrawShape(gfx::ICanvas& canvas, const std::string& id)
{
	if (!m_shapes.contains(id))
	{
		throw std::invalid_argument("Shape with this id doesn't exist");
	}
	m_shapes.at(id)->Draw(canvas);
}

void Picture::DrawPicture(gfx::ICanvas& canvas)
{
	for (auto& shape : m_shapes)
	{
		shape.second->Draw(canvas);
	}
}

std::vector<std::string> Picture::List() const
{
	std::vector<std::string> result;

	unsigned counter = 1;

	for (auto& shape : m_shapes)
	{
		result.push_back
		(
			std::to_string(counter) + " "
			+ shape.second->GetShapeType() + " "
			+ shape.second->GetId() + " "
			+ shape.second->GetShapeInfo()
		);
		counter++;
	}

	return result;
}

void Picture::ChangeColor(const std::string& id, const gfx::Color& color)
{
	if (!m_shapes.contains(id))
	{
		throw std::invalid_argument("Shape with this id doesn't exist");
	}

	m_shapes.at(id)->SetColor(color);
}

void Picture::ChangeShape(const std::string& id, std::unique_ptr<shapes::IShapeStrategy> strategy)
{
	if (!m_shapes.contains(id))
	{
		throw std::invalid_argument("Shape with this id doesn't exist");
	}

	m_shapes.at(id)->SetShapeStrategy(move(strategy));
}

std::shared_ptr<Shape> shapes::Picture::GetShapeById(const std::string& id) const
{
	auto it = m_shapes.find(id);
	if (!m_shapes.contains(id))
	{
		throw std::invalid_argument("Shape with this id doesn't exist");
	}

	return m_shapes.at(id);
}
