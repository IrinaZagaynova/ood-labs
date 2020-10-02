#pragma once
#include "IObserver.h"
#include "Event.h"
#include <set>

template <typename T, typename Event>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T, Event>& observer, size_t priority, const std::set<Event>& events) = 0;
	virtual void RemoveObserver(IObserver<T, Event>& observer) = 0;
	virtual void NotifyObservers(const std::set<Event>& changedEvents) = 0;
	virtual void UnsubscribeFromEvent(IObserver<T, Event>& observer, const Event& event) = 0;
	virtual void SubscribeToEvent(IObserver<T, Event>& observer, const Event& event) = 0;
};
