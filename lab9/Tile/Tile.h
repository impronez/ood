#pragma once
#include <array>
#include <cassert>
#include <cstdint>

#include "../Geom.h"

class Tile
{
public:
    // Размер тайла 8*8 пикселей.
    constexpr static int SIZE = 8;

    // Конструктор по умолчанию. Заполняет тайл указанным цветом.
    explicit Tile(uint32_t color = 0) noexcept
    {
        /* Реализуйте недостающий код самостоятельно. */
        for (int y = 0; y < SIZE; ++y)
        {
            for (int x = 0; x < SIZE; ++x)
            {
                m_pixels[y][x] = color;
            }
        }

        // -------------- не удалять ------------
        assert(m_instanceCount >= 0);
        ++m_instanceCount; // Увеличиваем счётчик тайлов (для целей тестирования).
        // -------------- не удалять ------------
    }

    Tile(const Tile& other)
    {
        /* Реализуйте недостающий код самостоятельно. */
        m_pixels = other.m_pixels;
        // -------------- не удалять ------------
        assert(m_instanceCount >= 0);
        ++m_instanceCount; // Увеличиваем счётчик тайлов (для целей тестирования).
        // -------------- не удалять ------------
    }

    ~Tile()
    {
        // -------------- не удалять ------------
        --m_instanceCount; // Уменьшаем счётчик тайлов.
        assert(m_instanceCount >= 0);
        // -------------- не удалять ------------
    }

    /**
     * Изменяет цвет пикселя тайла.
     * Если координаты выходят за пределы тайла, метод ничего не делает.
     */
    void SetPixel(Point p, uint32_t color) noexcept
    {
        /* Реализуйте недостающий код самостоятельно. */
        if (IsValidPoint(p))
        {
            m_pixels[p.y][p.x] = color; // Устанавливаем цвет пикселя
        }
    }

    /**
     * Возвращает цвет пикселя. Если координаты выходят за пределы тайла, возвращается пробел.
     */
    [[nodiscard]] uint32_t GetPixel(Point p) const noexcept
    {
        /* Реализуйте недостающий функционал самостоятельно. */
        if (IsValidPoint(p))
        {
            return m_pixels[p.y][p.x]; // Возвращаем цвет пикселя
        }
        return 0;
    }

    // Возвращает количество экземпляра класса Tile в программе.
    static int GetInstanceCount() noexcept
    {
        // -------------- не удалять ------------
        return m_instanceCount;
        // -------------- не удалять ------------
    }

private:

    [[nodiscard]] static bool IsValidPoint(Point p)
    {
        return p.x >= 0 && p.x < SIZE && p.y >= 0 && p.y < SIZE;
    }
    // -------------- не удалять ------------
    inline static int m_instanceCount = 0;
    // -------------- не удалять ------------

    /* Разместите здесь поля для хранения пикселей тайла. */
    std::array<std::array<uint32_t, SIZE>, SIZE> m_pixels {};
};