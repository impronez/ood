#pragma once
#include <string>
#include <memory>

#include "CShape.h"

class IShapeFactory
{
public:
	virtual std::unique_ptr<CShape> CreateShape(const std::string& description) = 0;
	
	virtual ~IShapeFactory() {}
};