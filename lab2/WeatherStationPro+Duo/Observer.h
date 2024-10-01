#pragma once

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <memory>

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
	virtual void RegisterObserver(std::shared_ptr<IObserver<T>> observer, unsigned priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(std::shared_ptr<IObserver<T>> observer) = 0;
};

// Реализация интерфейса IObservable
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
				observer->Update(data, this);
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
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	std::map<unsigned, std::unordered_set<ObserverPtr>> m_priorityToObservers;
	std::unordered_map<std::shared_ptr<ObserverType>, unsigned> m_observerToPriority;
};

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, const CObservable<T>* observable) = 0;
	virtual ~IObserver() = default;
};