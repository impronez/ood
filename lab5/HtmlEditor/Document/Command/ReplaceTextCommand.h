#pragma once
#include <vector>
#include "CCommand.h"
#include "../CDocumentItem.h"

class ReplaceTextCommand : public CCommand
{
public:
    ReplaceTextCommand(
        std::string newText,
        const size_t position,
        std::vector<CDocumentItem> &items
    )
        : m_newText(std::move(newText)),
        m_position(position),
        m_items(items)
    {}

    void DoExecute() override
    {
        if (m_position >= m_items.size())
        {
            throw std::invalid_argument("Position out of range");
        }

        auto item = m_items.at(m_position);
        const auto paragraph = item.GetParagraph();

        if (paragraph == nullptr)
        {
            throw std::invalid_argument("This item is not a text");
        }

        m_previousText = paragraph->GetText();
        paragraph->SetText(m_newText);
    }

    void DoUnexecute() override
    {
        if (m_position >= m_items.size())
        {
            throw std::invalid_argument("Position out of range");
        }

        auto item = m_items.at(m_position);
        const auto paragraph = item.GetParagraph();

        if (paragraph == nullptr)
        {
            throw std::invalid_argument("This item is not a text");
        }

        m_newText = paragraph->GetText();
        paragraph->SetText(m_previousText);
    }

    bool Merge(const ICommand& other) override
    {
        if (const auto replaceCmd = dynamic_cast<const ReplaceTextCommand*>(&other))
        {
            auto item = m_items.at(m_position);
            const auto paragraph = item.GetParagraph();

            m_newText = replaceCmd->m_newText;

            paragraph->SetText(m_newText);

            return true;
        }
        else
        {
            return false;
        }
    }

    void Destroy() override
    {}

private:
    std::string m_previousText {};
    std::string m_newText;
    size_t m_position;
    std::vector<CDocumentItem> &m_items;
};
