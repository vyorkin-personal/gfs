#pragma once

#include "Example.hpp"

struct VelocityComponent: public ecs::Component {
    VelocityComponent(const Vector2f& vec): vector{vec} {}
};
