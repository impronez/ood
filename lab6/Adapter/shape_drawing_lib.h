#pragma once
#include "graphics_lib.h"

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{
    struct Point
    {
        int x;
        int y;
    };

    // Интерфейс объектов, которые могут быть нарисованы на холсте из graphics\_lib
    class ICanvasDrawable
    {
    public:
        virtual void Draw(graphics_lib::ICanvas& canvas)const = 0;
        virtual ~ICanvasDrawable() = default;
    };

    class CTriangle : public ICanvasDrawable
    {
    public:
        CTriangle(const Point& p1, const Point& p2, const Point& p3)
            : m_point1(p1),
            m_point2(p2),
            m_point3(p3)
        {}

        void Draw(graphics_lib::ICanvas& canvas)const override
        {
            canvas.MoveTo(m_point1.x, m_point1.y);
            canvas.LineTo(m_point2.x, m_point2.y);

            canvas.LineTo(m_point3.x, m_point3.y);

            canvas.MoveTo(m_point2.x, m_point2.y);
            canvas.LineTo(m_point3.x, m_point3.y);
        }
    private:
        Point m_point1;
        Point m_point2;
        Point m_point3;
    };

    class CRectangle : public ICanvasDrawable
    {
    public:
        CRectangle(const Point& leftTop, int width, int height)
            : m_leftTop(leftTop),
            m_width(width),
            m_height(height)
        {}

        void Draw(graphics_lib::ICanvas& canvas)const override
        {
            canvas.MoveTo(m_leftTop.x, m_leftTop.y);
            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);

            canvas.LineTo(m_leftTop.x, m_leftTop.y - m_height);

            canvas.MoveTo(m_leftTop.x + m_width, m_leftTop.y - m_height);
            canvas.LineTo(m_leftTop.x, m_leftTop.y - m_height);

            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
        }
    private:
        Point m_leftTop;
        int m_width;
        int m_height;
    };

    // Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
    class CCanvasPainter
    {
    public:
        CCanvasPainter(graphics_lib::ICanvas& canvas)
            : m_canvas(canvas)
        {}

        void Draw(const ICanvasDrawable& drawable)
        {
            drawable.Draw(m_canvas);
        }
    private:
        graphics_lib::ICanvas& m_canvas;
    };
}