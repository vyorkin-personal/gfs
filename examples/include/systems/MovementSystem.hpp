#pragma once

#include "System.hpp"

#include "components/PositionComponent.hpp"
#include "components/VelocityComponent.hpp"

class MovementSystem: public gfs::System {
    public:
        virtual void initialize() {
            watchComponents<VelocityComponent, PositionComponent>();
        }

        virtual void processEntity(gfs::Entity* entity, const float delta) {
            auto pos = entity->getComponent<PositionComponent>();
            auto vel = entity->getComponent<VelocityComponent>();

            auto dx = vel->getX() * delta;
            auto dy = vel->getY() * delta;

            pos->move(dx, dy);
        }
};
