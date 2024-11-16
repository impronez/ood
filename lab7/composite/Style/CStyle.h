#pragma once

#include "IStyle.h"
#include "../CommonTypes.h"

class CStyle final : public IStyle
{
public:
    [[nodiscard]] bool IsEnabled() const override
    {
        return m_isEnabled;
    }

    void Enable(const bool enable) override
    {
        m_isEnabled = enable;
    }

    [[nodiscard]] std::optional<RGBAColor> GetColor() const override
    {
        return m_color;
    }

    void SetColor(RGBAColor color) override
    {
        m_color = color;
    }

    bool operator==(const CStyle& other) const
    {
        return m_isEnabled == other.m_isEnabled && m_color == other.m_color;
    }

private:
    bool m_isEnabled = false;
    std::optional<RGBAColor> m_color {};
};