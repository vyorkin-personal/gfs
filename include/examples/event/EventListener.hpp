#pragma once

#include "examples/Example.hpp"
#include "examples/event/ExplosionEvent.hpp"

class EventListener {
    public:
	EventListener(EventBus& eventBus, int* marker): marker{marker} {
	    eventBus.subscribe<ExplosionEvent>(this, &EventListener::onExplosion);
	}

	void onExplosion(const ExplosionEvent& event) {
	    (*marker) = 2;
	}

	int* marker;
};
