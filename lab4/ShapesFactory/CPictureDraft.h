#pragma once
#include <vector>
#include <memory>
#include "CShape.h"

class CPictureDraft
{
public:
    typedef std::vector<std::unique_ptr<CShape>> Storage;

    void AddShape(std::unique_ptr<CShape>&& shape)
    {
        m_shapes.push_back(std::move(shape));
    }

    size_t GetShapesCount() const
    {
        return m_shapes.size();
    }

    CShape& GetShape(const size_t index) const
    {
        if (index >= GetShapesCount())
        {
            throw std::range_error("Error, shapes index out of range");
        }

        return *m_shapes[index];
    }

    Storage::iterator begin() {
        return m_shapes.begin();
    }

    Storage::iterator end() {
        return m_shapes.end();
    }

    Storage::const_iterator begin() const {
        return m_shapes.begin();
    }

    Storage::const_iterator end() const {
        return m_shapes.end();
    }

private:
    Storage m_shapes;
};