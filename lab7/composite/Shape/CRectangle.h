#pragma once
#include "CShape.h"

class CRectangle final : public CShape
{
public:
    static constexpr std::string TYPE = "rectangle";

    CRectangle(const RectD& rect, std::shared_ptr<IStyle> const& lineStyle, std::shared_ptr<IStyle> const& fillStyle)
        : CShape(rect, lineStyle, fillStyle)
    {}

    [[nodiscard]] std::optional<RectD> GetFrame() const override
    {
        return m_rect;
    }

    void SetFrame(double left, double top, double width, double height) override
    {
        m_rect.left = left;
        m_rect.top = top;
        m_rect.width = width;
        m_rect.height = height;
    }

    std::string GetType() override
    {
        return TYPE;
    }

private:
    void DrawImpl(ICanvas & canvas) const override
    {
        canvas.MoveTo(m_rect.left, m_rect.top);
        canvas.LineTo(m_rect.left + m_rect.width, m_rect.top);

        canvas.MoveTo(m_rect.left + m_rect.width, m_rect.top);
        canvas.LineTo(m_rect.left + m_rect.width, m_rect.top + m_rect.height);

        canvas.MoveTo(m_rect.left + m_rect.width, m_rect.top + m_rect.height);
        canvas.LineTo(m_rect.left, m_rect.top + m_rect.height);

        canvas.MoveTo(m_rect.left, m_rect.top + m_rect.height);
        canvas.LineTo(m_rect.left, m_rect.top);
    }
};
