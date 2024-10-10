#pragma once

#include "CShape.h"

class CEllipse : public CShape
{
public:
    CEllipse(CColor color, Point center, double horizontalRadius, double verticalRadius)
        : CShape(color),
        m_center(center),
        m_horizontalRadius(horizontalRadius),
        m_verticalRadius(verticalRadius)
    {}

    void Draw(ICanvas& canvas) const override
    {
        canvas.SetColor(GetColor());
        canvas.DrawEllipse(m_center.x, m_center.y, m_horizontalRadius, m_verticalRadius);
    }

    Point GetCenter() const
    {
        return m_center;
    }

    double GetHorizontalRadius() const
    {
        return m_horizontalRadius;
    }

    double GetVerticalRadius() const
    {
        return m_verticalRadius;
    }

private:
    Point m_center;
    double m_horizontalRadius;
    double m_verticalRadius;
};