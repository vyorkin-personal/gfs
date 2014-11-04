#pragma once

#include "Example.hpp"
#include "components/PositionComponent.hpp"
#include "components/VelocityComponent.hpp"

class MovementSystem: public ecs::System {
    public:
        virtual void initialize() {
            watchComponents<VelocityComponent, PositionComponent>();
        }

        virtual void processEntity(ecs::Entity* entity, const float delta) {
            auto pos = entity->getComponent<PositionComponent>();
            auto vel = entity->getComponent<VelocityComponent>();

            pos->move(vel->vector * delta);
        }
};
