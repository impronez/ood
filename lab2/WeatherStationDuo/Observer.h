#pragma once
#include <functional>
#include <algorithm>
#include <map>
#include <unordered_set>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver;

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, unsigned priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, unsigned priority) override
	{
		if (!m_priorityToObservers.contains(priority))
		{
			m_priorityToObservers.insert({ priority, {} });
		}

		m_priorityToObservers.at(priority).insert(&observer);
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

	void RemoveObserver(ObserverType& observer)
	{
		for (auto& [priority, observers] : m_priorityToObservers)
		{
			if (observers.erase(&observer) > 0)
			{
				return;
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	std::map<unsigned, std::unordered_set<ObserverType*>> m_priorityToObservers;
};

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};