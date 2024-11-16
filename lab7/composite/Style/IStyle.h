#pragma once

#include <optional>

#include "../CommonTypes.h"

class IStyle
{
public:
    virtual bool IsEnabled() const = 0;

    virtual void Enable(bool enable) = 0;

    virtual std::optional<RGBAColor> GetColor() const = 0;

    virtual void SetColor(RGBAColor color) = 0;

    virtual ~IStyle() = default;
};