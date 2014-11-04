#pragma once

#include "Example.hpp"

class PlayerStateComponent: public ecs::Component {
    public:
	PlayerStateComponent(int hp):
	    initialHealth{hp}, health{hp} {}

	int getHealth() const {
	    return health;
	}

	void heal(int points) {
	    health += points;
	}

	void hit() {
	    health--;
	}

	void kill() {
	    health = 0;
	}

	void resurrect() {
	    health = initialHealth;
	}

    private:
	int initialHealth;
	int health;
};
