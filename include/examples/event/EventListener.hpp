#pragma once

#include "examples/Example.hpp"
#include "examples/event/ExplosionEvent.hpp"

class EventListener {
    public:
	EventListener(EventBus& eventBus) {
	    eventBus.subscribe<ExplosionEvent>(this, &EventListener::onExplosion);
	}

	void onExplosion(ExplosionEvent& event) {
	    event.finished = true;
	}
};
