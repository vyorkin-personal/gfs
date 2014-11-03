#pragma once

#include "System.hpp"

#include "components/InputComponent.hpp"

class InputSystem: public gfs::System {
    public:
        virtual void initialize() {
            watchComponents<InputComponent>();
        }

        virtual void processEntity(gfs::Entity* entity, const float delta) {
            auto input = entity->getComponent<InputComponent>();
            if (input->isMoving())
                input->stop();
            else
                input->move();
        }
};
