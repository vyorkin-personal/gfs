#pragma once

#include "examples/Example.hpp"

struct VelocityComponent: public Component {
    VelocityComponent(const float dx, const float dy):
	vector{Vector2f(dx, dy)} {}
    VelocityComponent(const Vector2f& vec): vector{vec} {}

    Vector2f vector;
};
