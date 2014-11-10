#pragma once

#include "examples/Example.hpp"

struct ExplosionEvent: public Event {
    ExplosionEvent(const float radius):
	radius{radius} {}

    float radius;
    bool finished;
};
