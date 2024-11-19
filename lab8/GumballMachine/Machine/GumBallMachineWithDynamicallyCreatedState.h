#pragma once
#include <format>
#include <iostream>
#include <memory>

namespace with_dynamic_state
{

	struct IState
	{
		virtual void InsertQuarter() = 0;
		virtual void EjectQuarter() = 0;
		virtual void TurnCrank() = 0;
		virtual void Dispense() = 0;
		[[nodiscard]] virtual std::string ToString()const = 0;
		virtual ~IState() = default;
	};

	struct IGumballMachine
	{
		virtual void ReleaseBall() = 0;
		[[nodiscard]] virtual unsigned GetBallCount()const = 0;

		virtual void SetSoldOutState() = 0;
		virtual void SetNoQuarterState() = 0;
		virtual void SetSoldState() = 0;
		virtual void SetHasQuarterState() = 0;

		virtual ~IGumballMachine() = default;
	};

	class CSoldState final : public IState
	{
	public:
		explicit CSoldState(IGumballMachine & gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}
		void InsertQuarter() override
		{
			std::cout << "Please wait, we're already giving you a gumball\n";
		}
		void EjectQuarter() override
		{
			std::cout << "Sorry you already turned the crank\n";
		}
		void TurnCrank() override
		{
			std::cout << "Turning twice doesn't get you another gumball\n";
		}
		void Dispense() override
		{
			m_gumballMachine.ReleaseBall();
			if (m_gumballMachine.GetBallCount() == 0)
			{
				std::cout << "Oops, out of gumballs\n";
				m_gumballMachine.SetSoldOutState();
			}
			else
			{
				m_gumballMachine.SetNoQuarterState();
			}
		}
		[[nodiscard]] std::string ToString() const override
		{
			return "delivering a gumball";
		}
	private:
		IGumballMachine & m_gumballMachine;
	};

	class CSoldOutState final : public IState
	{
	public:
		explicit CSoldOutState(IGumballMachine & gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You can't insert a quarter, the machine is sold out\n";
		}
		void EjectQuarter() override
		{
			std::cout << "You can't eject, you haven't inserted a quarter yet\n";
		}
		void TurnCrank() override
		{
			std::cout << "You turned but there's no gumballs\n";
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}
		[[nodiscard]] std::string ToString() const override
		{
			return "sold out";
		}
	private:
		IGumballMachine & m_gumballMachine;
	};

	class CHasQuarterState final : public IState
	{
	public:
		explicit CHasQuarterState(IGumballMachine & gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You can't insert another quarter\n";
		}
		void EjectQuarter() override
		{
			std::cout << "Quarter returned\n";
			m_gumballMachine.SetNoQuarterState();
		}
		void TurnCrank() override
		{
			std::cout << "You turned...\n";
			m_gumballMachine.SetSoldState();
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}
		[[nodiscard]] std::string ToString() const override
		{
			return "waiting for turn of crank";
		}
	private:
		IGumballMachine & m_gumballMachine;
	};

	class CNoQuarterState final : public IState
	{
	public:
		explicit CNoQuarterState(IGumballMachine & gumballMachine)
			: m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You inserted a quarter\n";
			m_gumballMachine.SetHasQuarterState();
		}
		void EjectQuarter() override
		{
			std::cout << "You haven't inserted a quarter\n";
		}
		void TurnCrank() override
		{
			std::cout << "You turned but there's no quarter\n";
		}
		void Dispense() override
		{
			std::cout << "You need to pay first\n";
		}
		[[nodiscard]] std::string ToString() const override
		{
			return "waiting for quarter";
		}
	private:
		IGumballMachine & m_gumballMachine;
	};

	class CGumballMachine final : private IGumballMachine
	{
	public:
		explicit CGumballMachine(unsigned numBalls)
			: m_count(numBalls)
		{

			if (m_count > 0)
			{
				SetNoQuarterState();
			}
			else
			{
				SetSoldOutState();
			}
		}
		void EjectQuarter() const
		{
			m_currentState->EjectQuarter();
		}
		void InsertQuarter() const
		{
			m_currentState->InsertQuarter();
		}
		void TurnCrank() const
		{
			m_currentState->TurnCrank();
			m_currentState->Dispense();
		}
		[[nodiscard]] std::string ToString()const
		{
			return std::format(R"(
		Mighty Gumball, Inc.
		C++-enabled Standing Gumball Model #2016 (with state)
		Inventory: {} gumball{}
		Machine is {}
		)",
				m_count,
				(m_count != 1 ? "s" : ""),
				m_currentState->ToString()
			);
		}
	private:
		[[nodiscard]] unsigned GetBallCount() const override
		{
			return m_count;
		}
		void ReleaseBall() override
		{
			if (m_count != 0)
			{
				std::cout << "A gumball comes rolling out the slot...\n";
				--m_count;
			}
		}
		void SetSoldOutState() override
		{
			m_currentState.reset(new CSoldOutState(*this));
		}
		void SetNoQuarterState() override
		{
			m_currentState.reset(new CNoQuarterState(*this));
		}
		void SetSoldState() override
		{
			m_currentState.reset(new CSoldState(*this));
		}
		void SetHasQuarterState() override
		{
			m_currentState.reset(new CHasQuarterState(*this));
		}

		unsigned m_count = 0;
		std::unique_ptr<IState> m_currentState{};
	};

}