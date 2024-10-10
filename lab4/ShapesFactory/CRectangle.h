#pragma once

#include "CShape.h"

class CRectangle : public CShape
{
public:
    CRectangle(CColor color, Point leftTop, double width, double height)
        : CShape(color),
        m_leftTop(leftTop),
        m_width(width),
        m_height(height)
    {}

    void Draw(ICanvas& canvas) const override
    {
        canvas.SetColor(GetColor());
        canvas.DrawLine(m_leftTop.x, m_leftTop.y, m_leftTop.x + m_width, m_leftTop.y);
        canvas.DrawLine(m_leftTop.x + m_width, m_leftTop.y, m_leftTop.x + m_width, m_leftTop.y + m_height);
        canvas.DrawLine(m_leftTop.x + m_width, m_leftTop.y + m_height, m_leftTop.x, m_leftTop.y + m_height);
        canvas.DrawLine(m_leftTop.x, m_leftTop.y + m_height, m_leftTop.x, m_leftTop.y);
    }

    Point GetLeftTop() const
    {
        return m_leftTop;
    }

    double GetWidth() const
    {
        return m_width;
    }

    double GetHeight() const
    {
        return m_height;
    }

private:
    Point m_leftTop;
    double m_width;
    double m_height;
};