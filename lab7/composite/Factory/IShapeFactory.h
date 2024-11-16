#pragma once

class IShape;

class IShapeFactory
{
public:
    virtual std::shared_ptr<IShape> CreateShape(std::istringstream& params) = 0;

    virtual ~IShapeFactory() = default;
};
