#pragma once
#include <cstdint>
#include <iosfwd>
#include <string>
#include <vector>

#include "../CoW.h"
#include "../Geom.h"
#include "../Tile/Tile.h"

class Image
{
public:
    /**
     * Конструирует изображение заданного размера. Если размеры не являются положительными,
     * выбрасывает исключение std::out_of_range.
     */
    explicit Image(Size size, uint32_t color = 0)
        : m_size(size),
        m_tiles(size.height, std::vector<CoW<Tile>>(size.width, CoW<Tile>(Tile(color))))
    {}

    // Возвращает размер изображения в пикселях.
    [[nodiscard]] Size GetSize() const noexcept
    {
        return m_size;
    }

    /**
     * Возвращает «цвет» пикселя в указанных координатах.Если координаты выходят за пределы
     * изображения, возвращает «пробел».
     */
    [[nodiscard]] uint32_t GetPixel(Point p) const noexcept
    {
        if (!IsPointInSize(p, m_size))
        {
            return 0;
        }

        int tileX = p.x / Tile::SIZE;
        int tileY = p.y / Tile::SIZE;
        int pixelX = p.x % Tile::SIZE;
        int pixelY = p.y % Tile::SIZE;

        return m_tiles[tileY][tileX]->GetPixel({ pixelX, pixelY });
    }

    /**
     * Задаёт «цвет» пикселя в указанных координатах. Если координаты выходят за пределы изображения
     * действие игнорируется.
     */
    void SetPixel(Point p, uint32_t color)
    {
        if (!IsPointInSize(p, m_size))
        {
            return; // Игнорируем установку цвета, если координаты выходят за пределы
        }

        int tileX = p.x / Tile::SIZE;
        int tileY = p.y / Tile::SIZE;
        int pixelX = p.x % Tile::SIZE;
        int pixelY = p.y % Tile::SIZE;

        // Используем метод Write для изменения тайла
        m_tiles[tileY][tileX].Write([&](Tile& tile) {
            tile.SetPixel({ pixelX, pixelY }, color);
        });
    }

private:
    Size m_size;
    std::vector<std::vector<CoW<Tile>>> m_tiles;
};



