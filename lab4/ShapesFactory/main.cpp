#include <iostream>
#include "CDesigner.h"
#include "CShapeFactory.h"
#include "CClient.h"
#include "SVGCanvas.h"

void PrintInfo()
{
    std::cout << "Commands:\n"
        << "triangle <hex-color> <x1> <y1> <x2> <y2> <x3> <y3>\n"
        << "rectangle <hex-color> <left top x> <left top y> <width> <height>\n"
        << "regularpolygon <hex-color> <center x> <center y> <verticles count> <radius>\n"
        << "ellipse <hex-color> <center x> <center y> <horizontal radius> <vertical radius>\n"
        << std::endl;
}

int main()
{
    SVGCanvas canvas;
    CShapeFactory shapeFactory;
    CDesigner designer(shapeFactory);
    CPainter painter;
    CClient client(designer);

    PrintInfo();

    client.HandleCommand(std::cin, canvas, painter);

    canvas.Save("output.svg");
}