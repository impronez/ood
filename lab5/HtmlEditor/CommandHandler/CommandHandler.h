#pragma once
#include "../Document/CDocument.h"
#include "../Menu/Menu.h"

class CommandHandler
{
public:
	CommandHandler()
	{
		m_menu.AddItem(
			"InsertParagraph",
			"Usage: InsertParagraph <position>|end <text>. Inserts a paragraph into the specified position.",
			[&](std::istringstream &params) { InsertParagraph(params); }
		);

		m_menu.AddItem(
			"InsertImage",
			"Usage: InsertImage <position>|end <width> <height> <image-path>. Inserts an image with the specified width and height.",
			[&](std::istringstream &params) { InsertImage(params); }
		);

		m_menu.AddItem(
			"SetTitle",
			"Usage: SetTitle <title>. Sets the document title.",
			[&](std::istringstream &params) { SetTitle(params); }
		);

		m_menu.AddItem(
			"List",
			"Usage: List. Displays the title and list of document elements.",
			[&](std::istringstream &params) { List(); }
		);

		m_menu.AddItem(
			"ReplaceText",
			"Usage: ReplaceText <position> <text>. Replaces the text in the paragraph by the specified position.",
			[&](std::istringstream &params) { ReplaceText(params); }
		);

		m_menu.AddItem(
			"ResizeImage",
			"Usage: ResizeImage <position> <width> <height>. Resizes the image at the specified position.",
			[&](std::istringstream &params) { ResizeImage(params); }
		);

		m_menu.AddItem(
			"DeleteItem",
			"Usage: DeleteItem <position>. Deletes an item at the specified position.",
			[&](std::istringstream &params) { DeleteItem(params); }
		);

		m_menu.AddItem(
			"Help",
			"Usage: Help. Shows the available commands.",
			[&](std::istringstream &params) { Help(); }
		);

		m_menu.AddItem(
			"Undo",
			"Usage: Undo. Cancels the last action.",
			[&](std::istringstream &params) { Undo(); }
		);

		m_menu.AddItem(
			"Redo",
			"Usage: Redo. Repeats the last canceled action.",
			[&](std::istringstream &params) { Redo(); }
		);

		m_menu.AddItem(
			"Save",
			"Usage: Save <path>. Saves the document to a file.",
			[&](std::istringstream &params) { Save(params); }
		);

		m_menu.AddItem(
			"Exit",
			"Usage: Exit. Exits the program.",
			[&](std::istringstream &params) { Exit(); }
		);
	}

	void InsertParagraph(std::istringstream &params)
	{
		std::string positionInput;
		std::string text;

		if (!(params >> positionInput && std::getline(params, text)))
		{
			std::cerr << "Invalid arguments." << std::endl;
			return;
		}

		std::optional<size_t> position = std::nullopt;
		if (positionInput != "end")
		{
			try
			{
				position = std::stoi(positionInput);
				--position.value();
			}
			catch (std::invalid_argument &)
			{
				std::cerr << "Error: The position must be an uint or 'end'." << std::endl;
				return;
			}
		}

		m_document.InsertParagraph(text, position);
	}

	void InsertImage(std::istringstream &params)
	{
		std::string positionInput;
		unsigned width;
		unsigned height;
		std::string imagePath;

		if (!(params >> positionInput >> width >> height >> imagePath))
		{
			std::cerr << "Invalid arguments." << std::endl;
			return;
		}

		if (width > MAX_IMAGE_SIZE || height > MAX_IMAGE_SIZE)
		{
			std::cerr << "Size must be between 1 and 10000\n";
			return;
		}

		std::optional<size_t> position = std::nullopt;
		if (positionInput != "end")
		{
			try
			{
				position = std::stoi(positionInput);
				--position.value();
			}
			catch (std::invalid_argument &)
			{
				std::cerr << "Error: The position must be an integer or 'end'." << std::endl;;
				return;
			}
		}

		m_document.InsertImage(imagePath, width, height, position);
	}

	void SetTitle(std::istringstream &params)
	{
		std::string newTitle;
		std::getline(params, newTitle);
		m_document.SetTitle(newTitle);
	}

	void List() const
	{
		const auto title = m_document.GetTitle();
		const auto itemCount = m_document.GetItemsCount();

		std::cout << "Title: " << title << std::endl;
		for (int i = 0; i < itemCount; ++i)
		{
			auto item = m_document.GetItem(i);
			auto image = item.GetImage();
			auto paragraph = item.GetParagraph();
			std::string description{};

			if (image != nullptr)
			{
				description = std::format("Image: {} {} {}", image->GetWidth(), image->GetHeight(),
				                          image->GetPath());
			}

			if (paragraph != nullptr)
			{
				description = std::format("Paragraph: {}", paragraph->GetText());
			}

			std::cout << i + 1 << ". " << description << std::endl;
		}
	}

	void ReplaceText(std::istringstream &params)
	{
		size_t position;
		std::string newText;

		if (!(params >> position && std::getline(params, newText)))
		{
			std::cerr << "Invalid arguments." << std::endl;
			return;
		}

		if (newText.empty())
		{
			std::cerr << "Error: text cannot be empty." << std::endl;
			return;
		}

		m_document.ReplaceText(newText, --position);
	}

	void ResizeImage(std::istringstream &params)
	{
		size_t position;
		unsigned newWidth;
		unsigned newHeight;

		if (!(params >> position >> newWidth >> newHeight))
		{
			std::cerr << "Invalid arguments." << std::endl;
			return;
		}

		m_document.ResizeImage(newWidth, newHeight, --position);
	}

	void DeleteItem(std::istringstream &params)
	{
		size_t position;
		if (!(params >> position))
		{
			std::cerr << "Invalid arguments." << std::endl;
			return;
		}
		m_document.DeleteItem(--position);
	}

	void Help() const
	{
		m_menu.ShowInstructions();
	}

	void Undo()
	{
		if (!m_document.CanUndo())
		{
			std::cout << "Cancellation is not possible!" << std::endl;
			return;
		}

		m_document.Undo();
	}

	void Redo()
	{
		if (!m_document.CanRedo())
		{
			std::cout << "Repeat is not possible!" << std::endl;
			return;
		}

		m_document.Redo();
	}

	void Save(std::istringstream &params)
	{
		std::string filePath;
		if (!(params >> filePath))
		{
			std::cerr << "Invalid arguments." << std::endl;
			return;
		}
		m_document.Save(filePath);
	}

	void Exit()
	{
		if (!m_document.IsSaved())
		{
			m_document.ClearHistory();
		}
		m_menu.Exit();
	}

	void Run()
	{
		m_menu.Run();
	}

private:
	static constexpr size_t MAX_IMAGE_SIZE = 10000;
	Menu m_menu{};
	CDocument m_document{};
};
