#pragma once
#include "IParagraph.h"

class CParagraph final : public IParagraph
{
public:
    explicit CParagraph(std::string text)
        : m_text(std::move(text))
    {}
    std::string GetText() const override
    {
        return m_text;
    }

    void SetText(const std::string &text) override
    {
        m_text = text;
    }
private:
    std::string m_text;
};