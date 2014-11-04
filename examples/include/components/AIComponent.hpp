#pragma once

#include "Example.hpp"

class AIComponent: public ecs::Component {
    public:
	AIComponent(bool idling = true) {
	    this->idling = idling;
	}

	bool isIdling() const {
	    return idling;
	}

	void nextState() {
	    idling = !idling;
	}

    private:
	bool idling;
};
