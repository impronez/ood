#ifndef DUCK_H
#define DUCK_H

#include "DanceBehavior.h"
#include "FlyBehavior.h"
#include "QuackBehavior.h"

#include <cassert>
#include <iostream>
#include <memory>

class Duck
{
public:
	Duck(FlyBehavior&& flyBehavior,
		QuackBehavior&& quackBehavior,
		DanceBehavior&& danceBehavior)
		: m_danceBehavior(std::move(danceBehavior)),
		m_flyBehavior(std::move(flyBehavior)),
		m_quackBehavior(std::move(quackBehavior))
	{
		assert(m_danceBehavior);
		assert(m_flyBehavior);
		assert(m_quackBehavior);
	}

	void Sound() const
	{
		m_quackBehavior();
	}

	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
		m_flyBehavior();
	}

	void Dance()
	{
		m_danceBehavior();
	}

	void SetFlyBehavior(FlyBehavior&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = std::move(flyBehavior);
	}

	void SetDanceBehavior(DanceBehavior&& danceBehavior)
	{
		assert(danceBehavior);
		m_danceBehavior = std::move(danceBehavior);
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
};

#endif