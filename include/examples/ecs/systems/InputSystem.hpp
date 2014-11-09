#pragma once

#include "examples/Example.hpp"
#include "examples/ecs/components/InputComponent.hpp"

class InputSystem: public System {
    public:
        virtual void initialize() override {
            watchComponents<InputComponent>();
        }

        virtual void processEntity(Entity* entity) override {
            auto input = entity->getComponent<InputComponent>();
            if (input->isMoving())
                input->stop();
            else
                input->move();
        }
};
