#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include "Image.h"

class ImageService
{
public:
    static void Print(const Image& img, std::ostream& out)
    {
        const auto size = img.GetSize();
        for (int y = 0; y < size.height; ++y)
        {
            for (int x = 0; x < size.width; ++x)
            {
                out.put(img.GetPixel({ x, y }));
            }
            out.put('\n');
        }
    }

/**
 * Загружает изображение из pixels. Линии изображения разделяются символами \n.
 * Размеры картинки определяются по количеству переводов строки и самой длинной линии.
 */
    static Image LoadImage(const std::string& pixels)
    {
        std::istringstream s(pixels);
        Size size{};
        std::string line;
        while (std::getline(s, line))
        {
            size.width = std::max(size.width, static_cast<int>(line.length()));
            ++size.height;
        }

        Image img(size);

        s = std::istringstream(pixels);
        for (int y = 0; y < size.height; ++y)
        {
            if (!std::getline(s, line))
                break;

            int x = 0;
            for (char ch : line)
            {
                img.SetPixel({ x++, y }, ch);
            }
        }

        return img;
    }

    static void SaveImageToPPM(const Image& image, const std::string& filename)
    {
        std::ofstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open the file for writing");
        }

        file << "P3\n";
        file << image.GetSize().width << " " << image.GetSize().height << "\n";
        file << "255\n";

        for (int y = 0; y < image.GetSize().height; ++y)
        {
            for (int x = 0; x < image.GetSize().width; ++x)
            {
                uint32_t color = image.GetPixel({x, y});

                uint8_t r = (color >> 16) & 0xFF;
                uint8_t g = (color >> 8) & 0xFF;
                uint8_t b = color & 0xFF;

                file << static_cast<int>(r) << " "
                     << static_cast<int>(g) << " "
                     << static_cast<int>(b) << " ";
            }
            file << "\n";
        }

        file.close();
    }
};