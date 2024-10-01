#pragma once

#include <map>
#include <unordered_map>
#include <unordered_set>
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
	virtual void RegisterObserver(std::shared_ptr<IObserver<T>> observer, unsigned priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(std::shared_ptr<IObserver<T>> observer) = 0;
};

// ���������� ���������� IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;
	typedef std::shared_ptr<ObserverType> ObserverPtr;

	void RegisterObserver(std::shared_ptr<ObserverType> observer, unsigned priority) override
	{
		m_priorityToObservers[priority].insert(observer);
		m_observerToPriority[observer] = priority;
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();

		auto copyObservers = m_priorityToObservers;
		for (auto it = copyObservers.rbegin(); it != copyObservers.rend(); ++it)
		{
			for (auto& observer : it->second)
			{
				observer->Update(data);
			}
		}
	}

	void RemoveObserver(std::shared_ptr<ObserverType> observer)
	{
		auto it = m_observerToPriority.find(observer);

		if (it != m_observerToPriority.end())
		{
			unsigned priority = it->second;
			auto& observers = m_priorityToObservers[priority];

			if (observers.contains(observer))
			{
				observers.erase(observer);
			}

			m_observerToPriority.erase(it);
		}
	}

protected:
	// ������-���������� ������ ����������� ������ �����, 
	// � ������� ���������� ���������� �� ���������� � �������
	virtual T GetChangedData() const = 0;

private:
	std::map<unsigned, std::unordered_set<ObserverPtr>> m_priorityToObservers;
	std::unordered_map<std::shared_ptr<ObserverType>, unsigned> m_observerToPriority;
};