#pragma once

#include <map>
#include <unordered_map>
#include <set>
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
	virtual void RegisterObserver(const std::shared_ptr<IObserver<T>>& observer, unsigned priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(const std::shared_ptr<IObserver<T>>& observer) = 0;
};

template <class T>
struct WeakPtrComparator
{
	bool operator()(const std::weak_ptr<IObserver<T>>& wp1, const std::weak_ptr<IObserver<T>>& wp2) const
	{
		auto sp1 = wp1.lock();
		auto sp2 = wp2.lock();

		if (sp1 && sp2)
		{
			return sp1 < sp2; 
		}
		return !sp1 && sp2;
	}
};

// ���������� ���������� IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;
	typedef std::weak_ptr<ObserverType> ObserverPtr;

	void RegisterObserver(const std::shared_ptr<ObserverType>& observer, unsigned priority) override
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
				if (auto ptr = observer.lock())
				{
					ptr.get()->Update(data);
				}
				else
				{
					unsigned priority = it->first;
					m_priorityToObservers[priority].erase(ptr);
					m_observerToPriority.erase(ptr);
				}
			}
		}
	}

	void RemoveObserver(const std::shared_ptr<ObserverType>& observer)
	{
		auto it = m_observerToPriority.find(observer);

		if (it != m_observerToPriority.end())
		{
			unsigned priority = it->second;
			auto& observers = m_priorityToObservers[priority];

			observers.erase(observer);

			m_observerToPriority.erase(it);
		}
	}

protected:
	// ������-���������� ������ ����������� ������ �����, 
	// � ������� ���������� ���������� �� ���������� � �������
	virtual T GetChangedData() const = 0;

private:
	std::map<unsigned, std::set<ObserverPtr, WeakPtrComparator<T>>> m_priorityToObservers;
	std::unordered_map<std::shared_ptr<ObserverType>, unsigned> m_observerToPriority;
};