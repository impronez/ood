#pragma once
#include <algorithm>
#include <array>

#include "CShape.h"

class CTriangle final : public CShape
{
public:
    static constexpr std::string TYPE = "triangle";

    CTriangle(const RectD& rect,
        const std::shared_ptr<IStyle> &lineStyle,
        const std::shared_ptr<IStyle> &fillStyle)
        : CShape(rect, lineStyle, fillStyle)
    {}

    [[nodiscard]] std::optional<RectD> GetFrame() const override
    {
        return m_rect;
    }

    void SetFrame(double left, double top, double width, double height) override
    {
        double oldLeft = m_rect.left;
        double oldTop = m_rect.top;
        double oldWidth = m_rect.width;
        double oldHeight = m_rect.height;

        m_rect.left = left;
        m_rect.top = top;
        m_rect.width = width;
        m_rect.height = height;
    }

    void DrawImpl(ICanvas & canvas) const override
    {
        auto points = GetPointsFromRect();
        canvas.MoveTo(points[0].x, points[0].y);
        canvas.LineTo(points[1].x, points[1].y);
        
        canvas.MoveTo(points[1].x, points[1].y);
        canvas.LineTo(points[2].x, points[2].y);
        
        canvas.MoveTo(points[2].x, points[2].y);
        canvas.LineTo(points[0].x, points[0].y);
    }

    std::string GetType() override
    {
        return TYPE;
    }

private:
    std::array<PointD, 3> GetPointsFromRect() const
    {
        std::array<PointD, 3> points;
        points[0] = PointD(m_rect.left, m_rect.top + m_rect.height);
        points[1] = PointD(m_rect.left + (m_rect.width / 2), m_rect.top);
        points[2] = PointD(m_rect.left + m_rect.width, m_rect.top + m_rect.height);

        return points;
    }
};
