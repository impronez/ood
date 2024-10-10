#pragma once

#include <set>
#include <functional>
#include <unordered_set>
#include <map>
#include <memory>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
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

// Реализация интерфейса IObservable
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
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData()const = 0;

private:
	std::map<int, std::unordered_set<ObserverType*>> m_priorityToObservers;
	std::unordered_map<ObserverType*, int> m_observerToPriority;
};
