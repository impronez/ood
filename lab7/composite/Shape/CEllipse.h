#pragma once
#include "CShape.h"

class CEllipse final : public CShape
{
public:
    static constexpr std::string Type = "ellipse";

    CEllipse(const RectD& rect, const std::shared_ptr<IStyle> &lineStyle, const std::shared_ptr<IStyle> &fillStyle)
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
        return Type;
    }
private:

    void DrawImpl(ICanvas & canvas) const override
    {
        canvas.DrawEllipse(m_rect.left, m_rect.top, m_rect.width, m_rect.height);
    }
};
