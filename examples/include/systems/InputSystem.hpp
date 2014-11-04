#pragma once

#include "Example.hpp"
#include "components/InputComponent.hpp"

class InputSystem: public ecs::System {
    public:
        virtual void initialize() {
            watchComponents<InputComponent>();
        }

        virtual void processEntity(ecs::Entity* entity, const float delta) {
            auto input = entity->getComponent<InputComponent>();
            if (input->isMoving())
                input->stop();
            else
                input->move();
        }
};
