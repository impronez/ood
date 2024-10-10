#pragma once

#include "CShape.h"

class CTriangle : public CShape
{
public:
    CTriangle(CColor color, Point point1, Point point2, Point point3)
        : CShape(color),
        m_vertex1(point1),
        m_vertex2(point2),
        m_vertex3(point3)
    {}

    void Draw(ICanvas& canvas) const override
    {
        canvas.SetColor(GetColor());
        canvas.DrawLine(m_vertex1.x, m_vertex1.y, m_vertex2.x, m_vertex2.y);
        canvas.DrawLine(m_vertex2.x, m_vertex2.y, m_vertex3.x, m_vertex3.y);
        canvas.DrawLine(m_vertex3.x, m_vertex3.y, m_vertex1.x, m_vertex1.y);
    }

    Point GetVertex1() const
    {
        return m_vertex1;
    }

    Point GetVertex2() const
    {
        return m_vertex2;
    }

    Point GetVertex3() const
    {
        return m_vertex3;
    }

private:
    Point m_vertex1;
    Point m_vertex2;
    Point m_vertex3;
};