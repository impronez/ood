#include "PictureController.h"
#include <iostream>
#include <sstream>
#include <regex>
#include "ShapeStrategyCreator.h"

using namespace controllers;

static bool IsValidHexColor(const std::string& hex)
{
	std::regex regex = std::regex("^#([A-Fa-f0-9]{6}|[A-Fa-f0-9]{3})$");

	return regex_match(hex, regex);
}

PictureController::PictureController(shapes::Picture& picture, gfx::ICanvas& canvas)
	: m_picture(picture),
	m_canvas(canvas)
{
	m_commands.emplace("AddShape", std::bind(&PictureController::HandleAddShapeCommand, this, std::placeholders::_1));
	m_commands.emplace("DeleteShape", std::bind(&PictureController::HandleDeleteShapeCommand, this, std::placeholders::_1));
	m_commands.emplace("DrawShape", std::bind(&PictureController::HandleDrawShapeCommand, this, std::placeholders::_1));
	m_commands.emplace("DrawPicture", std::bind(&PictureController::HandleDrawPictureCommand, this, std::placeholders::_1));
	m_commands.emplace("ChangeColor", std::bind(&PictureController::HandleChangeColorCommand, this, std::placeholders::_1));
	m_commands.emplace("ChangeShape", std::bind(&PictureController::HandleChangeShapeCommand, this, std::placeholders::_1));
	m_commands.emplace("List", std::bind(&PictureController::HandleListCommand, this, std::placeholders::_1));
	m_commands.emplace("MoveShape", std::bind(&PictureController::HandleMoveShapeCommand, this, std::placeholders::_1));
	m_commands.emplace("MovePicture", std::bind(&PictureController::HandleMovePictureCommand, this, std::placeholders::_1));
}

bool PictureController::HandleCommand(const std::string& line)
{
	std::istringstream input(line);

	std::string action;
	input >> action;

	auto it = m_commands.find(action);

	if (it != m_commands.end())
	{
		it->second(input);

		return true;
	}

	return false;
}

void PictureController::HandleAddShapeCommand(std::istream& input)
{
	std::string id, color;

	input >> id >> color;

	if (id.empty() || !IsValidHexColor(color))
	{
		throw std::invalid_argument("Invalid command arguments");
	}

	try
	{
		auto strategy = shapes::ShapeStrategyCreator::CreateFromStream(input);
		m_picture.AddShape(id, color, move(strategy));
	}
	catch (std::exception const& err)
	{
		std::cout << err.what() << std::endl;
	}
}

void PictureController::HandleDeleteShapeCommand(std::istream& input)
{
	std::string id;

	input >> id;

	if (id.empty())
	{
		throw std::invalid_argument("invalid command arguments, template: <id>");
	}

	m_picture.DeleteShape(id);
}

void PictureController::HandleMoveShapeCommand(std::istream& input)
{
	std::string id, dxStr, dyStr;

	input >> id >> dxStr >> dyStr;

	if (id.empty() || dxStr.empty() || dyStr.empty())
	{
		throw std::invalid_argument("invalid command arguments, template: <id> <delta x> <delta y>");
	}

	try
	{
		double dx = stod(dxStr);
		double dy = stod(dyStr);
		m_picture.GetShapeById(id)->Move(dx, dy);
	}
	catch (...)
	{
		throw std::invalid_argument("incorrect params");
	}
}

void PictureController::HandleMovePictureCommand(std::istream& input)
{
	std::string dxStr, dyStr;

	input >> dxStr >> dyStr;

	if (dxStr.empty() || dyStr.empty())
	{
		throw std::invalid_argument("invalid command arguments, template: <delta x> <delta y>");
	}

	try
	{
		double dx = stod(dxStr);
		double dy = stod(dyStr);
		m_picture.MovePicture(dx, dy);
	}
	catch (...)
	{
		throw std::invalid_argument("incorrect params");
	}
}

void PictureController::HandleDrawShapeCommand(std::istream& input)
{
	std::string id;

	input >> id;

	if (id.empty())
	{
		throw std::invalid_argument("invalid command arguments, template: <id>");
	}

	m_picture.DrawShape(m_canvas, id);
}

void PictureController::HandleDrawPictureCommand(std::istream& input)
{
	m_picture.DrawPicture(m_canvas);
}

void PictureController::HandleListCommand(std::istream& input)
{
	for (auto const& shapeInfo : m_picture.List())
	{
		std::cout << shapeInfo << std::endl;
	}
}

void PictureController::HandleChangeColorCommand(std::istream& input)
{
	std::string id, color;

	input >> id >> color;

	if (id.empty() || !IsValidHexColor(color))
	{
		throw std::invalid_argument("invalid command arguments, template: <id> <hex color>");
	}

	m_picture.GetShapeById(id)->SetColor(color);
}

void PictureController::HandleChangeShapeCommand(std::istream& input)
{
	std::string id;

	input >> id;

	if (id.empty())
	{
		throw std::invalid_argument("invalid command arguments, template: <id> <shape type> <shape args>");
	}

	try
	{
		auto strategy = shapes::ShapeStrategyCreator::CreateFromStream(input);
		m_picture.GetShapeById(id)->SetShapeStrategy(move(strategy));
	}
	catch (std::exception const& err)
	{
		std::cout << err.what() << std::endl;
	}
}
