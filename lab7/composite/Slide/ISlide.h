#pragma once
#include <limits>
#include <memory>

#include "../Shape/IShape.h"

class ISlide
{
public:
    virtual double GetWidth() const = 0;

    virtual double GetHeight() const = 0;

    virtual size_t GetShapesCount() const = 0;

    virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;

    virtual void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) = 0;

    virtual void InsertShapeGroup(const std::set<size_t>& indexes) = 0;

    virtual void RemoveShapeAtIndex(size_t index) = 0;

    virtual RGBAColor GetBackgroundColor() const = 0;

    virtual void SetBackgroundColor(RGBAColor color) = 0;

    virtual void Draw(ICanvas & canvas) const = 0;

    virtual ~ISlide() = default;
};
