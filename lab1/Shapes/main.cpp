#include <iostream>
#include <optional>
#include "Picture.h"
#include "PictureController.h"
#include "SVGCanvas.h"

using namespace shapes;

struct Args
{
	std::string outputFilename;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Invalid arguments" << std::endl;
		std::cout << "Usage: program.exe <output file name>" << std::endl;
		return std::nullopt;
	}

	Args args;
	args.outputFilename = argv[1];

	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return -1;
	}

	Picture picture;
	SVGCanvas canvas;
	controllers::PictureController controller(picture, canvas);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::string line;
		std::getline(std::cin, line);

		if (std::cin.eof() || std::cin.fail()) {
			break; 
		}

		try
		{
			if (!controller.HandleCommand(line))
			{
				std::cout << "Unknown command!" << std::endl;
			}	
			else
			{
				std::cout << "Command is executed!\n";
			}
		}
		catch (std::exception const& e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	canvas.Save(args->outputFilename);

	return 0;
}