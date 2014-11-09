#pragma once

#include "examples/Example.hpp"
#include "examples/ecs/components/PositionComponent.hpp"
#include "examples/ecs/components/VelocityComponent.hpp"

class MovementSystem: public System {
    public:
        virtual void initialize() override {
            watchComponents<VelocityComponent, PositionComponent>();
        }

        virtual void processEntity(Entity* entity) override {
            auto pos = entity->getComponent<PositionComponent>();
            auto vel = entity->getComponent<VelocityComponent>();

            pos->move(vel->vector * getDelta());
        }
};
