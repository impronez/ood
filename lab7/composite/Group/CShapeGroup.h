#pragma once
#include <limits>
#include <vector>

#include "../Shape/CShape.h"
#include "IShapeGroup.h"

class CShapeGroup final : public IShapeGroup, public std::enable_shared_from_this<CShapeGroup>
{
public:
    static constexpr std::string TYPE = "shape-group";

    explicit CShapeGroup(const std::vector<std::shared_ptr<IShape>>& shapes)
        : m_shapes(shapes)
    {
        if (shapes.empty())
        {
            throw std::invalid_argument("Shapes for shape group is empty");
        }
    }

    explicit CShapeGroup(const std::shared_ptr<IShape>& shape)
    {
        m_shapes.push_back(shape);
    }

    std::shared_ptr<IStyle> GetLineStyle() const override
    {
        if (m_shapes.empty())
        {
            return nullptr;
        }

        auto firstShapeStyle = m_shapes.front()->GetLineStyle();

        for (auto& shape: m_shapes)
        {
            if (shape == nullptr)
            {
                return nullptr;
            }

            if (shape == m_shapes.front())
            {
                continue;
            }

            auto style = shape->GetLineStyle();

            if (firstShapeStyle->GetColor() != style->GetColor())
            {
                return nullptr;
            }
        }

        return firstShapeStyle;
    }

    void SetLineStyle(RGBAColor color, bool isEnabled) override
    {
        for (auto& shape: m_shapes)
        {
            shape->SetLineStyle(color, isEnabled);
        }
    }

    std::shared_ptr<const IShape> GetShapeGroup() const override
    {
        return shared_from_this();
    }

    std::shared_ptr<IStyle> GetFillStyle() const override
    {
        if (m_shapes.empty())
        {
            return nullptr;
        }

        auto firstShapeStyle = m_shapes.front()->GetFillStyle();
        for (auto& shape: m_shapes)
        {
            if (shape == nullptr)
            {
                return nullptr;
            }

            if (shape == m_shapes.front())
            {
                continue;
            }

            auto style = shape->GetFillStyle();

            if (firstShapeStyle->GetColor() != style->GetColor())
            {
                return nullptr;
            }
        }

        return firstShapeStyle;
    }

    void SetFillStyle(RGBAColor color, bool isEnabled) override
    {
        for (auto& shape: m_shapes)
        {
            shape->SetFillStyle(color, isEnabled);
        }
    }

    std::shared_ptr<IShape> GetShapeGroup() override
    {
        return shared_from_this();
    }

    std::optional<RectD> GetFrame() const override
    {
        if (m_shapes.empty())
        {
            return std::nullopt;
        }

        double left = std::numeric_limits<double>::max();
        double top = std::numeric_limits<double>::max();
        double right = std::numeric_limits<double>::lowest();
        double bottom = std::numeric_limits<double>::lowest();

        for (const auto &shape: m_shapes)
        {
            auto shapeRect = shape->GetFrame();
            if (shapeRect.has_value())
            {
                left = std::min(left, shapeRect.value().left);
                top = std::min(top, shapeRect.value().top);
                right = std::max(right, shapeRect.value().left + shapeRect.value().width);
                bottom = std::max(bottom, shapeRect.value().top + shapeRect.value().height);
            }
            else
            {
                return std::nullopt;
            }
        }

        return RectD(left, top, right - left, bottom - top);
    }

    void SetFrame(double left, double top, double width, double height) override
    {
        if (m_shapes.empty())
        {
            return;
        }

        auto groupFrame = GetFrame();
        if (groupFrame.has_value())
        {
            auto scaleWidth = width / groupFrame.value().width;
            auto scaleHeight = height / groupFrame.value().height;

            for (auto& shape : m_shapes)
            {
                auto shapeFrame = shape->GetFrame();

                auto shapeLeftInGroupFrame = shapeFrame.value().left - groupFrame.value().left;
                auto shapeLeftDueScaling = shapeLeftInGroupFrame * scaleWidth;

                auto shapeTopInGroupFrame = shapeFrame.value().top - groupFrame.value().top;
                auto shapeTopDueScaling = shapeTopInGroupFrame * scaleHeight;

                shape->SetFrame(
                    left + shapeLeftDueScaling,
                    top + shapeTopDueScaling,
                    shapeFrame.value().width * scaleWidth,
                    shapeFrame.value().height * scaleHeight
                );
            }
        }
    }

    void Draw(ICanvas &canvas) const override
    {
        for (auto& shape : m_shapes)
        {
            shape->Draw(canvas);
        }
    }

    size_t GetShapesCount() const override
    {
        return m_shapes.size();
    }

    void InsertShape(const std::shared_ptr<IShape> &shape, size_t position = std::numeric_limits<size_t>::max()) override
    {
        if (position > m_shapes.size())
        {
            position = m_shapes.size();
        }
        m_shapes.insert(m_shapes.begin() + position, shape);
    }

    std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override
    {
        if (index >= m_shapes.size())
        {
            throw std::out_of_range("Index is out of range");
        }
        return m_shapes[index];
    }

    void RemoveShapeAtIndex(size_t index) override
    {
        if (index >= m_shapes.size())
        {
            throw std::out_of_range("Index is out of range");
        }
        m_shapes.erase(m_shapes.begin() + index);
    }

    std::string GetType() override
    {
        return TYPE;
    }
private:
    std::vector<std::shared_ptr<IShape>> m_shapes;
};
