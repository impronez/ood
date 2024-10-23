#pragma once
#include <iostream>
#include <format>

// ѕространство имен современной графической библиотеки (недоступно дл€ изменени€)
namespace modern_graphics_lib
{
    using namespace std;

    class CPoint
    {
    public:
        CPoint(int x, int y) :x(x), y(y) {}
        int x;
        int y;
    };

    //  ласс дл€ современного рисовани€ графики
    class CModernGraphicsRenderer
    {
    public:
        CModernGraphicsRenderer(ostream& strm)
            : m_out(strm)
        {}

        ~CModernGraphicsRenderer()
        {
            if (m_drawing) // «авершаем рисование, если оно было начато
            {
                EndDraw();
            }
        }

        // Ётот метод должен быть вызван в начале рисовани€
        void BeginDraw()
        {
            if (m_drawing)
            {
                throw logic_error("Drawing has already begun");
            }

            m_out << "<draw>" << endl;
            m_drawing = true;
        }

        // ¬ыполн€ет рисование линии
        void DrawLine(const CPoint& start, const CPoint& end)
        {
            if (!m_drawing)
            {
                throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
            }
            
            m_out << std::format(R"(  <line fromX="{}" fromY="{}" toX="{}" toY="{}"/>)", start.x, start.y, end.x, end.y)
                << std::endl;
        }

        // Ётот метод должен быть вызван в конце рисовани€
        void EndDraw()
        {
            if (!m_drawing)
            {
                throw logic_error("Drawing has not been started");
            }

            m_out << "</draw>" << endl;
            m_drawing = false;
        }
    private:
        ostream& m_out;
        bool m_drawing = false;
    };
}