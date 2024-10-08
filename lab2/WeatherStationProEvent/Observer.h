#pragma once

#include <map>
#include <unordered_map>
#include <set>
#include <memory>

const unsigned DEFAULT_PRIORITY = 5;

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T, typename EventType>
class IObserver;

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T, typename EventType>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(const std::shared_ptr<IObserver<T, EventType>>& observer, EventType eventType, unsigned priority) = 0;
	virtual void NotifyObservers(EventType eventType) = 0;
	virtual void RemoveObserver(const std::shared_ptr<IObserver<T, EventType>>& observer, EventType eventType) = 0;
};

template <class T, class EventType>
struct WeakPtrComparator
{
	bool operator()(const std::weak_ptr<IObserver<T,EventType>>& wp1,
		const std::weak_ptr<IObserver<T,EventType>>& wp2) const
	{
	//owner before
		auto sp1 = wp1.lock();
		auto sp2 = wp2.lock();

		if (sp1 && sp2)
		{
			return sp1 < sp2;
		}
		return !sp1 && sp2;
	}
};

// Реализация интерфейса IObservable
template <class T, class EventType>
class CObservable : public IObservable<T, EventType>
{
public:
	typedef IObserver<T, EventType> ObserverType;
	typedef std::weak_ptr<ObserverType> ObserverPtr;

	void RegisterObserver(const std::shared_ptr<ObserverType>& observer,
		EventType eventType,
		unsigned priority = DEFAULT_PRIORITY) override
	{
		m_priorityToObservers[eventType][priority].insert(observer);
		m_observerToPriority[observer] = priority;
	}

	void NotifyObservers(EventType eventType) override
	{
		T data = GetChangedData();

		auto copyObservers = m_priorityToObservers[eventType];
		for (auto& [priority, observers] : copyObservers)
		{
			for (auto& observer : observers)
			{
				if (auto ptr = observer.lock())
				{
					ptr.get()->Update(data, eventType);
				}
				else
				{
					m_priorityToObservers[eventType][priority].erase(ptr);
					m_observerToPriority.erase(ptr);
				}
			}
		}
	}

	void RemoveObserver(const std::shared_ptr<ObserverType>& observer, EventType eventType)
	{
		auto it = m_observerToPriority.find(observer);

		if (it != m_observerToPriority.end())
		{
			unsigned priority = it->second;
			auto& observers = m_priorityToObservers[eventType][priority];

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
	std::map<EventType, std::map<unsigned, std::set<ObserverPtr, WeakPtrComparator<T, EventType>>>> m_priorityToObservers;
	std::unordered_map<std::shared_ptr<ObserverType>, unsigned> m_observerToPriority;
};

template <typename T, typename EventType>
class IObserver
{
public:
	virtual void Update(T const& data, EventType eventType) = 0;
	virtual ~IObserver() = default;
};