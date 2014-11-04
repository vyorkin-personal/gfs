#pragma once

#include "Example.hpp"

struct PositionComponent: public ecs::Component {
    PositionComponent(const Point2f& point): point{point}

    void move(const Vector2f& speed) {
	point += speed;
    }

    Point2f point;
};
