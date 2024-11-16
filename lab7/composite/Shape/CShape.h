#pragma once

#include <memory>

#include "IShape.h"
#include "../CommonTypes.h"
#include "../Style/CStyle.h"
#include "../Canvas/ICanvas.h"

class CShape : public IShape
{
public:
    CShape(
        const RectD& rect,
        const std::shared_ptr<IStyle>& lineStyle,
        const std::shared_ptr<IStyle>& fillStyle)
        : m_rect(rect),
        m_lineStyle(lineStyle),
        m_fillStyle(fillStyle)
    {}

    std::shared_ptr<IStyle> GetLineStyle() const override
    {
        return m_lineStyle;
    }

    void SetLineStyle(RGBAColor color, bool isEnabled) override
    {
        m_lineStyle->SetColor(color);
        m_lineStyle->Enable(isEnabled);
    }

    std::shared_ptr<const IShape> GetShapeGroup() const override
    {
        return nullptr;
    }

    std::shared_ptr<IShape> GetShapeGroup() override
    {
        return nullptr;
    }

    [[nodiscard]] std::shared_ptr<IStyle> GetFillStyle() const override
    {
        return m_fillStyle;
    }

    void SetFillStyle(RGBAColor color, bool isEnabled) override
    {
        m_fillStyle->SetColor(color);
        m_fillStyle->Enable(isEnabled);
    }

    void Draw(ICanvas &canvas) const override
    {
        if (m_lineStyle != nullptr && m_lineStyle->IsEnabled() && m_lineStyle->GetColor().has_value())
        {
            canvas.SetLineColor(m_lineStyle->GetColor().value());
        }

        if (m_fillStyle != nullptr && m_fillStyle->IsEnabled() && m_fillStyle->IsEnabled())
        {
            canvas.BeginFill(m_fillStyle->GetColor().value());
        }

        DrawImpl(canvas);

        canvas.EndFill();
    }

protected:
    virtual void DrawImpl(ICanvas& canvas) const = 0;

    RectD m_rect {};

private:
    std::shared_ptr<IStyle> m_lineStyle;
    std::shared_ptr<IStyle> m_fillStyle;
};