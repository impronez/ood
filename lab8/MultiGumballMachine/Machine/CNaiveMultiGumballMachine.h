#pragma once

#include <format>

namespace naive
{
	struct IGumballMachine
	{
		virtual ~IGumballMachine() = default;

		virtual void SetHasQuarterState() = 0;
		virtual void SetNoQuarterState() = 0;
		virtual void SetSoldOutState() = 0;
		virtual void SetSoldState() = 0;
		virtual void Dispense() = 0;
	};

	class CNaiveMultiGumballMachine : public IGumballMachine
	{
	public:
		enum class State
		{
			SoldOut, // Жвачка закончилась
			NoQuarter, // Нет монетки
			HasQuarter, // Есть монетка
			Sold, // Монетка выдана
		};

		CNaiveMultiGumballMachine(unsigned count, std::ostream& out)
			: m_gumballCount(count),
			m_state(count > 0 ? State::NoQuarter : State::SoldOut),
			m_out(out)
		{}

		void InsertQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				m_out << "You can't insert a quarter, the machine is sold out\n";
				break;
			case State::NoQuarter:
				AddQuarter();
				m_state = State::HasQuarter;
				break;
			case State::HasQuarter:
				AddQuarter();
				break;
			case State::Sold:
				m_out << "Please wait, we're already giving you a gumball\n";
				break;
			}
		}

		void EjectQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::HasQuarter:
				m_out << "Quarter returned\n";
				m_state = State::NoQuarter;
				break;
			case State::NoQuarter:
				m_out << "You haven't inserted a quarter\n";
				break;
			case State::Sold:
				m_out << "Sorry you already turned the crank\n";
				break;
			case State::SoldOut:
				m_out << "You can't eject, you haven't inserted a quarter yet\n";
				break;
			}
		}

		void TurnCrank()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				m_out << "You turned but there's no gumballs\n";
				break;
			case State::NoQuarter:
				m_out << "You turned but there's no quarter\n";
				break;
			case State::HasQuarter:
				m_out << "You turned...\n";
				m_state = State::Sold;
				Dispense();
				break;
			case State::Sold:
				m_out << "Turning twice doesn't get you another gumball\n";
				break;
			}
		}

		void Refill(unsigned numBalls)
		{
			m_gumballCount = numBalls;
			m_state = numBalls > 0 ? State::NoQuarter : State::SoldOut;
		}

		[[nodiscard]] std::string ToString() const
		{
			std::string state = (m_state == State::SoldOut)
				? "sold out"
				: (m_state == State::NoQuarter)	 ? "waiting for quarter"
				: (m_state == State::HasQuarter) ? "waiting for turn of crank"
												 : "delivering a gumball";

			return std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: {} gumball{}
Machine is {}
)",
				m_gumballCount, m_gumballCount != 1 ? "s" : "", state);
		}

		void AddQuarter()
		{
			if (m_quarterCount < MAX_QUARTER_COUNT)
			{
				m_out << "You inserted a quarter\n";
				m_quarterCount++;
			}
		}

		void ReleaseAllQuarters()
		{
			m_quarterCount = 0;
			SetNoQuarterState();
		}

		void TakeQuarter()
		{
			if (m_quarterCount > 0)
			{
				m_quarterCount--;
			}

			if (m_quarterCount == 0)
			{
				if (m_gumballCount > 0)
				{
					SetNoQuarterState();
				}
				else
				{
					SetSoldOutState();
				}
			}
		}

		void ReleaseBall()
		{
			if (m_gumballCount > 0)
			{
				--m_gumballCount;
				if (m_gumballCount > 0)
				{
					if (m_quarterCount > 0)
					{
						SetHasQuarterState();
					}
					else
					{
						SetNoQuarterState();
					}
				}
				else
				{
					SetSoldOutState();
				}
			}
		}

		[[nodiscard]] unsigned GetQuarterCount() const
		{
			return m_quarterCount;
		}

		[[nodiscard]] unsigned GetGumballCount() const
		{
			return m_gumballCount;
		}

	private:
		void Dispense() override
		{
			using namespace std;
			switch (m_state)
			{
			case State::Sold:
				m_out << "A gumball comes rolling out the slot\n";
				--m_gumballCount;
				if (m_gumballCount == 0)
				{
					m_out << "Oops, out of gumballs\n";
					m_state = State::SoldOut;
				}
				else
				{
					m_state = State::NoQuarter;
				}
				break;
			case State::NoQuarter:
				m_out << "You need to pay first\n";
				break;
			case State::SoldOut:
			case State::HasQuarter:
				m_out << "No gumball dispensed\n";
				break;
			}
		}

		void SetSoldOutState() override
		{
			m_state = State::SoldOut;
		};

		void SetNoQuarterState() override
		{
			m_state = State::NoQuarter;
		};

		void SetSoldState() override
		{
			m_state = State::Sold;
		};

		void SetHasQuarterState() override
		{
			m_state = State::HasQuarter;
		};

		static constexpr unsigned MAX_QUARTER_COUNT = 5;

		unsigned m_quarterCount = 0;
		unsigned m_gumballCount;

		State m_state = State::SoldOut;

		std::ostream& m_out;
	};
}