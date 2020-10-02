#pragma once
#include <map>
#include "IObservable.h"

template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, size_t priority) override
	{
		m_observers.emplace(priority, &observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto copy = m_observers;
		for (auto& observer : copy)
		{
			observer.second->Update(data);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		for (auto iter = m_observers.begin(); iter != m_observers.end(); iter++)
		{
			if (iter->second == &observer)
			{
				m_observers.erase(iter);
				break;
			}
		}
	}

protected:
	virtual T GetChangedData()const = 0;

private:
	std::multimap<size_t, ObserverType*, std::greater<size_t>> m_observers;
};