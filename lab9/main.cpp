#include <iostream>

#include "Drawer/Drawer.h"
#include "Image/ImageService.h"


int main()
{
    {
        Image img = ImageService::LoadImage(
            " CCCC             \n"
            "CC  CC   ##    ## \n"
            "CC      ####  ####\n"
            "CC  CC   ##    ## \n"
            " CCCC             \n");
        ImageService::Print(img, std::cout);
    }

    {
        Image image({ 50, 50 }, '.');

        Drawer::DrawCircle(image, {24, 24}, 12, '#');
        Drawer::FillCircle(image, {24, 24}, 10, '#');

        Drawer::DrawLine(image, {0, 25}, {11, 25}, '#');
        Drawer::DrawLine(image, {37, 25}, {49, 25}, '#');

        Drawer::DrawLine(image, {24, 0}, {24, 11}, '#');
        Drawer::DrawLine(image, {24, 37}, {24, 49}, '#');

        Drawer::DrawLine(image, {33, 15}, {42, 7}, '#');
        Drawer::DrawLine(image, {5, 40}, {14, 32}, '#');


        Drawer::DrawLine(image, {7, 6}, {16, 14}, '#');
        Drawer::DrawLine(image, {34, 32}, {43, 40}, '#');

        ImageService::Print(image, std::cout);

    }

    {
        Image image({ 50, 50 }, 0);

        Drawer::DrawCircle(image, {24, 24}, 12, 0xFFFF00);
        Drawer::FillCircle(image, {24, 24}, 11, 0xFFFF00);

        Drawer::DrawLine(image, {0, 25}, {11, 25}, 0xFFFF00);
        Drawer::DrawLine(image, {37, 25}, {49, 25}, 0xFFFF00);

        Drawer::DrawLine(image, {24, 0}, {24, 11}, 0xFFFF00);
        Drawer::DrawLine(image, {24, 37}, {24, 49}, 0xFFFF00);

        Drawer::DrawLine(image, {33, 15}, {42, 7}, 0xFFFF00);
        Drawer::DrawLine(image, {5, 40}, {14, 32}, 0xFFFF00);


        Drawer::DrawLine(image, {7, 6}, {16, 14}, 0xFFFF00);
        Drawer::DrawLine(image, {34, 32}, {43, 40}, 0xFFFF00);

        ImageService::SaveImageToPPM(image, "sun.ppm");

    }
}