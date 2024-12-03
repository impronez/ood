#pragma once
#include <vector>

#include "CCommand.h"
#include "../CDocumentItem.h"

class DeleteItemCommand final : public CCommand
{
public:
    DeleteItemCommand(const size_t index, std::vector<CDocumentItem> &items)
        : m_index(index),
        m_items(items)
    {}

    void DoExecute() override
    {
        if (m_index >= m_items.size())
        {
            throw std::invalid_argument("Index out of range");
        }

        if (m_currentItem == nullptr)
        {
            m_currentItem = std::make_unique<CDocumentItem>(m_items.at(m_index));
        }

        m_currentItem->Remove();
        m_items.erase(m_items.begin() + m_index);
    }

    void DoUnexecute() override
    {
        if (m_currentItem == nullptr)
        {
            return;
        }

        m_items.insert(m_items.begin() + m_index, *m_currentItem);
        m_currentItem->Unremove();
    }

    bool Merge(const ICommand &other) override
    {
        return false;
    }

    void Destroy() override
    {}

private:
    size_t m_index;
    std::unique_ptr<CDocumentItem> m_currentItem;
    std::vector<CDocumentItem> &m_items;
};
