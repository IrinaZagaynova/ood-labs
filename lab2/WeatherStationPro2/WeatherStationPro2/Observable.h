#pragma once
#include <map>
#include "IObservable.h"

template <class T, class Event>
class CObservable : public IObservable<T, Event>
{
public:
	typedef IObserver<T, Event> ObserverType;

	void RegisterObserver(ObserverType& observer, size_t priority, const std::set<Event>& events) override
	{
		for (auto iter = m_observers.begin(); iter != m_observers.end(); iter++)
		{
			if (iter->second == &observer)
			{
				return;
			}
		}
		m_observers.emplace(priority, &observer);
		m_events.emplace(&observer, events);
	}

	void NotifyObservers(const std::set<Event>& changedEvents) override
	{
		T data = GetChangedData();
		auto copy = m_observers;
		for (auto& observer : copy)
		{
			for (auto event : changedEvents)
			{
				if (IsObserverSubscribedToEvent(*observer.second, event))
				{
					observer.second->Update(data, event);
				}
			}
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		for (auto iter = m_observers.begin(); iter != m_observers.end(); iter++)
		{
			if (iter->second == &observer)
			{
				m_observers.erase(iter);
				m_events.erase(m_events.find(&observer));
				return;
			}
		}
	}

	void UnsubscribeFromEvent(ObserverType& observer, const Event& event) override
	{
		auto iter = m_events.find(&observer);
		if (iter != m_events.end())
		{
			iter->second.erase(event);
		}
	}

	void SubscribeToEvent(ObserverType& observer, const Event& event) override
	{
		auto iter = m_events.find(&observer);
		if (iter != m_events.end() && !IsObserverSubscribedToEvent(observer, event))
		{
			iter->second.insert(event);
		}
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	bool IsObserverSubscribedToEvent(ObserverType& observer, const Event& event)
	{
		auto iter = m_events.find(&observer);
		if (iter != m_events.end())
		{
			for (auto item : iter->second)
			{
				if (item == event)
				{
					return true;
				}
			}
		}
		return false;
	}
private:
	std::multimap<size_t, ObserverType*, std::greater<size_t>> m_observers;
	std::map<ObserverType*, std::set<Event>> m_events;
};