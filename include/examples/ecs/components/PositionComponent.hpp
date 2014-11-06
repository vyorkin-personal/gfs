#pragma once

#include "examples/Example.hpp"

struct PositionComponent: public Component {
    PositionComponent(const float x, const float y):
	point{Vector2f(x, y)} {}
    PositionComponent(const Point2f& point): point{point} {}

    void move(const Vector2f& speed) {
	point += speed;
    }

    Point2f point;
};
