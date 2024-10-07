#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	explicit CBeverage(const std::string& description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	explicit CCoffee(const std::string& description = "Coffee")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 60;
	}
};

// Капучино
class CCappuccino : public CCoffee
{
public:
	explicit CCappuccino(bool isDoublePortion = false)
		: CCoffee(isDoublePortion ? "Double Cappuccino" : "Standard Cappuccino"),
		m_isDoublePortion(isDoublePortion)
	{}

	double GetCost() const override
	{
		return m_isDoublePortion ? 120 : 80;
	}
private:
	bool m_isDoublePortion;
};

// Латте
class CLatte : public CCoffee
{
public:
	explicit CLatte(bool isDoublePortion = false)
		:CCoffee(isDoublePortion ? "Double Latte" : "Standard Latte"),
		m_isDoublePortion(isDoublePortion)
	{}

	double GetCost() const override
	{
		return m_isDoublePortion ? 130 : 90;
	}
private:
	bool m_isDoublePortion;
};

enum class TeaType
{
	Black,
	Green,
	Herbal,
	Oolong
};
std::string TypeTeaString(TeaType type)
{
	switch (type)
	{
	case TeaType::Black:
		return "Black";
	case TeaType::Green:
		return "Green";
	case TeaType::Herbal:
		return "Herbal";
	case TeaType::Oolong:
		return "Oolong";
	default:
		return "Unknown type";
	}
}

// Чай
class CTea : public CBeverage
{
public:
	explicit CTea(TeaType type)
		:CBeverage(TypeTeaString(type) + " Tea"),
		m_type(type)
	{}

	double GetCost() const override
	{
		return 30;
	}
private:
	TeaType m_type;
};

enum class MilkshakeSize
{
	Small,
	Medium,
	Large,
};

std::string MilkshakeSizeString(MilkshakeSize sizeType)
{
	switch (sizeType)
	{
	case MilkshakeSize::Small:
		return "Small";
	case MilkshakeSize::Medium:
		return "Medium";
	case MilkshakeSize::Large:
		return "Large";
	default:                        
		return "Unknown Size";
	}
}


// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	explicit CMilkshake(MilkshakeSize size)
		: CBeverage(MilkshakeSizeString(size) + " Milkshake"),
		m_size(size)
	{}

	double GetCost() const override
	{
		return m_size == MilkshakeSize::Small ? 50
			: m_size == MilkshakeSize::Medium ? 60
			: 80;
	}
private:
	MilkshakeSize m_size;
};