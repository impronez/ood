#pragma once
#include "../picture/Picture.h"
#include <functional>

namespace controllers
{
	class PictureController
	{
	public:

		PictureController(shapes::Picture& picture, gfx::ICanvas& canvas);

		bool HandleCommand(const std::string& line);

	private:

		void HandleAddShapeCommand(std::istream& input);
		void HandleDeleteShapeCommand(std::istream& input);

		void HandleMoveShapeCommand(std::istream& input);
		void HandleMovePictureCommand(std::istream& input);

		void HandleDrawShapeCommand(std::istream& input);
		void HandleDrawPictureCommand(std::istream& input);

		void HandleListCommand(std::istream& input);

		void HandleChangeColorCommand(std::istream& input);
		void HandleChangeShapeCommand(std::istream& input);

		std::map<std::string, std::function<void(std::istream& input)>> m_commands;
		shapes::Picture& m_picture;
		gfx::ICanvas& m_canvas;
	};
}

