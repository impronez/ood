#pragma once

#include "../Image/Image.h"

class Drawer
{
public:
    /*static void DrawLine(Image& image, Point from, Point to, uint32_t color)
    {
        if (from.x > to.x)
        {
            std::swap(from, to);
        }

        int deltaX = std::abs(to.x - from.x);
        int deltaY = std::abs(to.y - from.y);

        int err = 0;
        int deltaErr = (deltaY + 1);

        int y = from.y;
        int dirY = to.y - from.y;

        if (dirY > 0)
        {
            dirY = 1;
        }
        else if (dirY < 0)
        {
            dirY = -1;
        }

        for (int x = from.x; x <= to.x; ++x)
        {
            image.SetPixel({x, y}, color);

            err += deltaErr;

            if (err >= (deltaX + 1))
            {
                y += dirY;
                err -= (deltaX + 1);
            }
        }
    }*/
    static void DrawLine(Image& image, Point from, Point to, uint32_t color)
    {
        const int deltaX = std::abs(to.x - from.x);
        const int deltaY = std::abs(to.y - from.y);

        if (deltaY > deltaX) // Отрезок крутой
        {
            DrawSteepLine(image, from, to, color);
        }
        else // Отрезок пологий
        {
            DrawSlopeLine(image, from, to, color);
        }
    }

    static void DrawCircle(Image& image, Point center, int radius, uint32_t color)
    {
        int x = radius;
        int y = 0;
        int radiusError = 1 - x;

        while (x >= y)
        {
            image.SetPixel({ center.x + x, center.y - y }, color);
            image.SetPixel({ center.x + x, center.y + y }, color);
            image.SetPixel({ center.x - x, center.y - y }, color);
            image.SetPixel({ center.x - x, center.y + y }, color);
            image.SetPixel({ center.x + y, center.y - x }, color);
            image.SetPixel({ center.x + y, center.y + x }, color);
            image.SetPixel({ center.x - y, center.y - x }, color);
            image.SetPixel({ center.x - y, center.y + x		}, color);

            y++;

            if (radiusError < 0)
            {
                radiusError += 2 * y + 1;
            }
            else
            {
                x--;
                radiusError += 2 * (y - x + 1);
            }
        }
    }

    static void FillCircle(Image& image, Point center, int radius, uint32_t color)
    {
        int x = radius;
        int y = 0;
        int radiusError = 1 - x;

        while (x >= y)
        {
            for (int i = center.x - x; i <= center.x + x; ++i)
            {
                image.SetPixel({ i, center.y - y }, color);
                image.SetPixel({ i, center.y + y }, color);
            }

            for (int i = center.x - y; i <= center.x + y; ++i)
            {
                image.SetPixel({ i, center.y - x }, color);
                image.SetPixel({ i, center.y + x }, color);
            }

            y++;

            if (radiusError < 0)
            {
                radiusError += 2 * y + 1;
            }
            else
            {
                x--;
                radiusError += 2 * (y - x + 1);
            }
        }
    }

private:
    static int Sign(int value)
    {
        return (0 < value) - (value < 0);
    }

    // Рисует крутой отрезок (для которого |to.y - from.y| >= |to.x - from.x|).
    static void DrawSteepLine(Image& image, Point from, Point to, uint32_t color)
    {
        const int deltaX = std::abs(to.x - from.x);
        const int deltaY = std::abs(to.y - from.y);

        assert(deltaY >= deltaX);

        if (from.y > to.y)
        { // Крутые отрезки рисуем снизу вверх.
            std::swap(from, to);
        }

        const int stepX = Sign(to.x - from.x); // Шаг по оси X (-1, 0 или 1).
        const int errorThreshold = deltaY + 1; // Порог увеличения координаты X.
        const int deltaErr = deltaX + 1; // Шаг увеличения порога.

        // Начальное значение ошибки устанавливается не в 0, а в deltaErr/2, отрезок получается диагональным.
        int error = deltaErr / 2;

        for (Point p = from; p.y <= to.y; ++p.y)
        {
            image.SetPixel({ p.x, p.y }, color);
            assert((p.y != to.y) || (p.x == to.x));

            error += deltaErr; // Увеличиваем ошибку увеличения координаты X.

            if (error >= errorThreshold)
            { // Если вышли за пределы текущего порога X
                p.x += stepX; // Смещаемся к следующему значению X
                error -= errorThreshold; // Уменьшаем ошибку
            }
        }
    }


    //Рисует пологий отрезок (для которого |to.y - from.y| < |to.x - from.x|).
    static void DrawSlopeLine(Image& image, Point from, Point to, uint32_t color)
    {
        const int deltaX = std::abs(to.x - from.x);
        const int deltaY = std::abs(to.y - from.y);

        assert(deltaX >= deltaY);

        if (from.x > to.x)
        { // Пологие отрезки рисуем слева направо.
            std::swap(from, to);
        }

        // Пологие отрезки рисуются по аналогии с крутыми.

        const int stepY = Sign(to.y - from.y);
        const int errorThreshold = deltaX + 1;
        const int deltaErr = deltaY + 1;

        int error = deltaErr / 2;

        for (Point p = from; p.x <= to.x; ++p.x)
        {
            image.SetPixel({ p.x, p.y }, color);
            assert((p.x != to.x) || (p.y == to.y));

            error += deltaErr;

            if (error >= errorThreshold)
            {
                p.y += stepY;
                error -= errorThreshold;
            }
        }
    }
};