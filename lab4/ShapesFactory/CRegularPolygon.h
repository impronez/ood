#pragma once

#include "CShape.h"
#include <cmath>
#include <numbers>

class CRegularPolygon : public CShape
{
public:
    CRegularPolygon(CColor color, Point center, int verticesCount, double radius)
        : CShape(color),
        m_center(center),
        m_verticesCount(verticesCount),
        m_radius(radius)
    {}

    void Draw(ICanvas& canvas) const override
    {
        canvas.SetColor(GetColor());

        double angleStep = 2 * std::numbers::pi / m_verticesCount;

        double startX = m_center.x + m_radius * std::cos(0);
        double startY = m_center.y + m_radius * std::sin(0);

        double prevX = startX;
        double prevY = startY;

        for (int i = 1; i <= m_verticesCount; ++i)
        {
            double angle = i * angleStep;
            double x = m_center.x + m_radius * std::cos(angle);
            double y = m_center.y + m_radius * std::sin(angle);

            canvas.DrawLine(prevX, prevY, x, y);

            prevX = x;
            prevY = y;
        }

        canvas.DrawLine(prevX, prevY, startX, startY);
    }

    Point GetCenter() const
    {
        return m_center;
    }

    int GetPointsCount() const
    {
        return m_verticesCount;
    }

    double GetRadius() const
    {
        return m_radius;
    }

private:
    Point m_center;
    int m_verticesCount;
    double m_radius;
};