#pragma once

#include "Example.hpp"
#include "components/PlayerStateComponent.hpp"

class PlayerSystem: public ecs::System {
    public:
        virtual void initialize() {
            watchTags({"player"});
        }

        virtual void processEntity(ecs::Entity* entity, const float delta) {
            auto state = entity->getComponent<PlayerStateComponent>();
            state->hit();
        }
};
