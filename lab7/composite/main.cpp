#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "CommandHandler.h"
#include "Canvas/SVGCanvas.h"
#include "Factory/CShapeFactory.h"
#include "Group/CShapeGroup.h"
#include "Shape/CEllipse.h"
#include "Shape/CRectangle.h"
#include "Shape/CTriangle.h"
#include "Slide/CSlide.h"

int main()
{
    auto factory = std::make_unique<CShapeFactory>();
    auto slide = std::make_unique<CSlide>();
    auto canvas = std::make_unique<SVGCanvas>(slide->GetWidth(), slide->GetHeight());

    CommandHandler handler(std::move(slide), std::move(canvas), std::move(factory));
    handler.Run();

    return 0;
}