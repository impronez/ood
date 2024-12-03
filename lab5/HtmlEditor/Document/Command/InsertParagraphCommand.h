#pragma once
#include <optional>
#include <vector>

#include "CCommand.h"
#include "../CDocumentItem.h"
#include "../Paragraph/CParagraph.h"

class InsertParagraphCommand final : public CCommand
{
public:
    InsertParagraphCommand(
        const std::string& text,
        const std::optional<size_t>position,
        std::vector<CDocumentItem>& items
    )
        : m_text(text),
        m_position(position),
        m_items(items)
    {}

    void DoExecute() override
    {
        auto paragraph = std::make_shared<CParagraph>(m_text);
        CDocumentItem docItem(paragraph);

        if (!m_position.has_value())
        {
            m_items.emplace_back(paragraph);
            m_position = m_items.size() - 1;
            return;
        }

        const size_t position = m_position.value();
        if (position >= m_items.size())
        {
            throw std::invalid_argument("Position out of range");
        }

        m_items.insert(m_items.begin() + position, docItem);
        m_item = docItem;
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
        }

        const size_t position = m_position.value();
        if (position < m_items.size())
        {
            m_items.erase(m_items.begin() + position);
        }
        m_position = std::nullopt;
    }

    bool Merge(const ICommand &other) override
    {
        return false;
        // if (const auto replaceCmd = dynamic_cast<const InsertParagraphCommand*>(&other))
        // {
        //     std::cout << m_text << std::endl;
        //     m_text = replaceCmd->m_text;
        //     std::cout << m_text << std::endl;
        // }
        // else
        // {
        //     throw std::logic_error("Cannot merge: other is not a SetTitleCommand.");
        // }
    }

    void Destroy() override
    {}

private:
    std::string m_text;
    std::optional<size_t> m_position;
    std::vector<CDocumentItem>& m_items;
    std::optional<CDocumentItem> m_item;
};
