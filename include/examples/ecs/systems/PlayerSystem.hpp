#pragma once

#include "examples/Example.hpp"
#include "examples/ecs/components/PlayerStateComponent.hpp"

class PlayerSystem: public System {
    public:
        virtual void initialize() {
            watchTags({"player"});
        }

        virtual void processEntity(Entity* entity, const float delta) {
            auto state = entity->getComponent<PlayerStateComponent>();
            state->hit();
        }
};
