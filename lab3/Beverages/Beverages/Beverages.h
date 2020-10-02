#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
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
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 60;
	}
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	enum class Portion
	{
		Standard,
		Double
	};

public:
	CCappuccino(Portion portion = Portion::Standard)
		:CCoffee((portion == Portion::Standard) ? "Cappuccino" : "Double Cappuccino"), m_portion(portion)
	{}

	double GetCost() const override
	{
		if (m_portion == Portion::Double)
		{
			return 120;
		}
		return 80;
	}

private:
	Portion m_portion;
};

// Латте
class CLatte : public CCoffee
{
public:
	enum class Portion
	{
		Standard,
		Double
	};

public:
	CLatte(Portion portion = Portion::Standard)
		:CCoffee((portion == Portion::Standard) ? "Latte" : "Double latte"), m_portion(portion)
	{}

	double GetCost() const override
	{
		if (m_portion == Portion::Double)
		{
			return 130;
		}
		return 90;
	}

private:
	Portion m_portion;
};

// Чай
class CTea : public CBeverage
{
public:
	enum class Sort 
	{
		Black,
		Green,
		Hibiscus,
		Chamomile
	};

public:
	CTea(Sort sort = Sort::Black)
		:CBeverage(SortToString(sort) + " tea"), m_sort(sort)
	{}

	double GetCost() const override
	{
		return 30;
	}

private:
	std::string SortToString(Sort sort)
	{
		switch (sort)
		{
		case Sort::Black:
			return "Black";
		case Sort::Green:
			return "Green";
		case Sort::Hibiscus:
			return "Hibiscus";
		case Sort::Chamomile:
			return "Chamomile";
		}
		return "";
	}

private:
	Sort m_sort;
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	enum class Portion
	{
		Small,
		Standart,
		Large
	};

public:
	CMilkshake(Portion portion = Portion::Standart)
		: CBeverage(PortionToString(portion) + " Milkshake"), m_portion(portion)
	{}

	double GetCost() const override
	{
		switch (m_portion)
		{
		case Portion::Small:
			return 50;
		case Portion::Standart:
			return 60;
		case Portion::Large:
			return 80;
		}
		return 0;
	}

private:
	std::string PortionToString(Portion portion)
	{
		switch (portion)
		{
		case Portion::Small:
			return "Small";
		case Portion::Standart:
			return "Standart";
		case Portion::Large:
			return "Large";
		}
		return "";
	}

private:
	Portion m_portion;
};
