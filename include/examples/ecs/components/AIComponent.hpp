#pragma once

#include "examples/Example.hpp"

class AIComponent: public Component {
    public:
	AIComponent(bool idling = true): idling{idling} {}

	bool isIdling() const {
	    return idling;
	}

	void nextState() {
	    idling = !idling;
	}

    private:
	bool idling;
};
