#pragma once

#include "examples/Example.hpp"
#include "examples/ecs/components/PlayerStateComponent.hpp"

class PlayerSystem: public System {
    public:
        virtual void initialize() override {
            watchTags({"player"});
        }

        virtual void processEntity(Entity* entity) override {
            auto state = entity->getComponent<PlayerStateComponent>();
            state->hit();
        }
};
