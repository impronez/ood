#pragma once
#include <format>
#include <optional>
#include <vector>

#include "CCommand.h"
#include "../Image/CImage.h"
#include "../CDocumentItem.h"
#include "../../Utils/FileUtils.h"

class InsertImageCommand : public CCommand
{
    public:
	InsertImageCommand(
		std::string path,
		const unsigned width,
		const unsigned height,
		const std::optional<size_t> position,
		std::vector<CDocumentItem> &items
	)
		: m_usrPath(std::move(path)),
		m_width(width),
		m_height(height),
		m_position(position),
		m_items(items)
	{}

	void DoExecute() override
	{
		if (!m_newPath.has_value())
		{
			m_newPath = SaveTempImage(m_usrPath);
		}

		const auto image = std::make_shared<CImage>(m_newPath.value(), m_width, m_height);
		const CDocumentItem documentItem(image);

		if (!m_position.has_value())
		{
			m_items.push_back(documentItem);
			return;
		}

		const size_t position = m_position.value();

		if (position > m_items.size())
		{
			throw std::invalid_argument("Position out of range");
		}

		m_items.insert(m_items.begin() + position, documentItem);
	}

	void DoUnexecute() override
	{
		if (m_items.empty())
		{
			return;
		}

		if (!m_position.has_value())
		{
			m_items.pop_back();
			return;
		}

		const size_t position = m_position.value();

		if (position < m_items.size())
		{
			m_items.erase(
				m_items.begin() + static_cast<std::vector<CDocumentItem>::iterator::difference_type>(position));
		}
	}

	bool Merge(const ICommand &other) override
	{
		return false;
	}

	void Destroy() override
	{
		if (m_newPath.has_value())
		{
			FileUtils::DeleteFileIfExists(m_newPath.value());
		}
	}

private:
	static std::string SaveTempImage(const std::string &path)
	{
		const auto extension = FileUtils::GetFileExtension(path);
		const auto newFilePath = std::format("images/{}", FileUtils::GenerateRandomFileName(extension));

		FileUtils::CopyFile(path, newFilePath);
		return newFilePath;
	}

	std::string m_usrPath;
	std::optional<std::string> m_newPath = std::nullopt;
	unsigned m_width;
	unsigned m_height;
	std::optional<size_t> m_position;
	std::vector<CDocumentItem> &m_items;
};
