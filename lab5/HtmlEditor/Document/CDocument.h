#pragma once
#include <vector>
#include "IDocument.h"
#include "Command/DeleteItemCommand.h"
#include "Command/InsertImageCommand.h"
#include "Command/InsertParagraphCommand.h"
#include "Command/ReplaceTextCommand.h"
#include "Command/ResizeImageCommand.h"
#include "Command/SetTitleCommand.h"
#include "History/History.h"
#include "../Utils/HtmlUtils.h"

class CDocumentItem;

class CDocument final : public IDocument
{
public:
    void InsertParagraph(const std::string &text, std::optional<size_t> position) override
    {
        m_history.AddAndExecute(std::make_unique<InsertParagraphCommand>(text, position, m_items));
    }

    void ReplaceText(const std::string &newText, size_t position) override
    {
        m_history.AddAndExecute(std::make_unique<ReplaceTextCommand>(newText, position, m_items), true);
    }

    void InsertImage(const std::string &path, int width, int height, std::optional<size_t> position) override
    {
        m_history.AddAndExecute(std::make_unique<InsertImageCommand>(path, width, height, position, m_items));
    }

    void ResizeImage(int width, int height, size_t position) override
    {
        m_history.AddAndExecute(std::make_unique<ResizeImageCommand>(position, width, height, m_items), true);
    }

    [[nodiscard]] size_t GetItemsCount() const override
    {
        return m_items.size();
    }

    CDocumentItem GetItem(const size_t index) const
    {
        if (index >= m_items.size())
        {
            throw std::invalid_argument("Index out of range");
        }

        return m_items[index];
    }

    void DeleteItem(size_t index) override
    {
        m_history.AddAndExecute(std::make_unique<DeleteItemCommand>(index, m_items));
    }

    [[nodiscard]] std::string GetTitle() const override
    {
        return m_title;
    }

    void SetTitle(const std::string &title) override
    {
        m_history.AddAndExecute(std::make_unique<SetTitleCommand>(m_title, title), true);
    }

    bool CanUndo() const override
    {
        return m_history.CanUndo();
    }

    void Undo() override
    {
        m_history.Undo();
    }

    [[nodiscard]] bool CanRedo() const override
    {
        return m_history.CanRedo();
    }

    void Redo() override
    {
        m_history.Redo();
    }


    void Save(const std::string &path) override
    {
        std::vector<CConstDocumentItem> constItems{};

        for (const auto &item: m_items)
        {
            constItems.emplace_back(static_cast<CConstDocumentItem>(item));
        }

        HtmlUtils::CreateHtmlFile(m_title, constItems, path);

        m_isSaved = true;
    }

    bool IsSaved() const
    {
        return m_isSaved;
    }

    void ClearHistory()
    {
        if (!IsSaved())
        {
            m_history.Clear();
        }
    }

private:
    std::string m_title;
    std::vector<CDocumentItem> m_items;
    History m_history;
    bool m_isSaved = false;
};
