#pragma once

#include <set>
#include <functional>
#include <unordered_set>
#include <map>
#include <memory>

/*
��������� ��������� IObserver. ��� ������ ������������� �����,
�������� �������� ����������� �� ���������������� IObservable
���������� ������� �������� ��� ���������,
������������� ����������� � ����� Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
��������� ��������� IObservable. ��������� ����������� � ���������� �� ����������, � �����
������������ �������� ����������� ������������������ ������������.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// ���������� ���������� IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		m_priorityToObservers[priority].insert(&observer);
		m_observerToPriority[&observer] = priority;
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto priorityToObserversCopy = m_priorityToObservers;

		for (auto it = priorityToObserversCopy.rbegin(); it != priorityToObserversCopy.rend(); ++it)
		{
			for (auto& observer : it->second)
			{
				observer->Update(data);
			}
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		auto it = m_observerToPriority.find(&observer);

		if (it != m_observerToPriority.end())
		{
			int priority = it->second;
			auto& observers = m_priorityToObservers[priority];

			if (observers.contains(&observer))
			{
				observers.erase(&observer);
			}

			m_observerToPriority.erase(it);
		}
	}

protected:
	// ������-���������� ������ ����������� ������ �����, 
	// � ������� ���������� ���������� �� ���������� � �������
	virtual T GetChangedData()const = 0;

private:
	std::map<int, std::unordered_set<ObserverType*>> m_priorityToObservers;
	std::unordered_map<ObserverType*, int> m_observerToPriority;
};
