#pragma once
#include "IObservable.h"
#include "Event.h"

template <typename T, typename Event>
class IObserver
{
public:
	virtual void Update(T const& data, const Event& event) = 0;
	virtual ~IObserver() = default;
};