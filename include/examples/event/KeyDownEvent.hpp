#pragma once

#include "examples/Example.hpp"

struct KeyDownEvent: public Event {
    KeyDownEvent(const char keyCode):
	keyCode{keyCode} {}

    char keyCode;
};
