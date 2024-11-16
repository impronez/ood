#pragma once
#include <limits>
#include <memory>
#include <vector>

#include "ISlide.h"
#include "../CommonTypes.h"
#include "../Canvas/ICanvas.h"

constexpr RGBAColor TRANSPARENT_COLOR = 0;

class CSlide final : public ISlide
{
public:
    CSlide(const double width = 1920, const double height = 1080)
        : m_width(width),
        m_height(height)
    {}

    [[nodiscard]] double GetWidth() const override
    {
        return m_width;
    }

    [[nodiscard]] double GetHeight() const override
    {
        return m_height;
    }

    [[nodiscard]] size_t GetShapesCount() const override
    {
        return m_shapes.size();
    }

    std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override
    {
        return m_shapes[index];
    }

    void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) override
    {
        auto it = position > m_shapes.size()
            ? m_shapes.end()
            : m_shapes.begin() + position;

        m_shapes.insert(it, shape);
    }

    void InsertShapeGroup(const std::set<size_t> &indexes) override
    {
        std::vector<std::shared_ptr<IShape>> groupShapes;
        for (auto index : indexes)
        {
            auto shape = GetShapeAtIndex(index);
            groupShapes.push_back(shape);
        }

        auto shapeGroup = std::make_shared<CShapeGroup>(groupShapes);

        for (int i = m_shapes.size() - 1; i >= 0; i--)
        {
            if (indexes.contains(i))
            {
                RemoveShapeAtIndex(i);
            }
        }

        InsertShape(shapeGroup);
    }

    void RemoveShapeAtIndex(size_t index) override
    {
        if (index >= m_shapes.size())
        {
            throw std::out_of_range("Invalid remove index of shape");
        }

        m_shapes.erase(m_shapes.begin() + index);
    }

    [[nodiscard]] RGBAColor GetBackgroundColor() const override
    {
        return m_backgroundColor;
    }

    void SetBackgroundColor(RGBAColor color) override
    {
        m_backgroundColor = color;
    }

    void Draw(ICanvas & canvas) const override
    {
        DrawSlide(canvas);

        for (auto& shape: m_shapes)
        {
            shape->Draw(canvas);
        }
    }

private:
    void DrawSlide(ICanvas& canvas) const
    {
        canvas.BeginFill(m_backgroundColor);

        canvas.MoveTo(0, 0);
        canvas.LineTo(0, m_height);
        canvas.LineTo(m_width, 0);

        canvas.MoveTo(m_width, m_height);
        canvas.LineTo(m_width, 0);
        canvas.LineTo(0, m_height);

        canvas.EndFill();
    }

    double m_width;
    double m_height;

    std::vector<std::shared_ptr<IShape>> m_shapes {};

    RGBAColor m_backgroundColor = TRANSPARENT_COLOR;
};
