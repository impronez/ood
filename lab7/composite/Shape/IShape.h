#pragma once
#include <memory>

#include "../Style/CStyle.h"
#include "../Canvas/ICanvas.h"

class IShape
{
public:
    virtual std::shared_ptr<IStyle> GetLineStyle() const = 0;
    virtual void SetLineStyle(RGBAColor color, bool isEnabled) = 0;

    virtual std::shared_ptr<IStyle> GetFillStyle() const = 0;
    virtual void SetFillStyle(RGBAColor color, bool isEnabled) = 0;

    virtual std::optional<RectD> GetFrame() const = 0;
    virtual void SetFrame(double left, double top, double width, double height) = 0;

    virtual void Draw(ICanvas & canvas) const = 0;

    virtual std::shared_ptr<IShape> GetShapeGroup() = 0;
    virtual std::shared_ptr<const IShape> GetShapeGroup() const = 0;

    virtual std::string GetType() = 0;

    virtual ~IShape() = default;
};
