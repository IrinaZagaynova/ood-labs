#pragma once
#include "IObserver.h"
#include "Event.h"
#include <set>

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;

	virtual void RegisterObserver(IObserver<T>& observer, size_t priority, const std::set<Event>& events) = 0;	
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers(const std::set<Event>& changedEvents) = 0;
	virtual void UnsubscribeFromEvent(IObserver<T>& observer, const Event& event) = 0;
	virtual void SubscribeToEvent(IObserver<T>& observer, const Event& event) = 0;
};
