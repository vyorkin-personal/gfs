#pragma once

#include "System.hpp"

#include "components/PlayerStateComponent.hpp"

class PlayerSystem: public gfs::System {
    public:
        virtual void initialize() {
            watchTags({"player"});
        }

        virtual void processEntity(gfs::Entity* entity, const float delta) {
            auto state = entity->getComponent<PlayerStateComponent>();
            state->hit();
        }
};
