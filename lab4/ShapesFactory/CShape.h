#pragma once
#include "Color.h"
#include "ICanvas.h"

class CShape
{
public:
	explicit CShape(const CColor color)
		: m_color(color)
	{}

	virtual void Draw(ICanvas& canvas) const = 0;

	CColor GetColor() const
	{
		return m_color;
	}

	virtual ~CShape() = default;

private:
	CColor m_color;
};