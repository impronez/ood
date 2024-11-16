#pragma once
#include "../Shape/IShape.h"
#include "../Shape/IShapes.h"

class IShapeGroup : public IShape, public IShapes
{
public:
    virtual ~IShapeGroup() = default;
};
