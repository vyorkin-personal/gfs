#pragma once

#include "Component.hpp"

class AIComponent: public gfs::Component {
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
