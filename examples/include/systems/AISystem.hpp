#pragma once

#include "System.hpp"

#include "components/AIComponent.hpp"

class AISystem: public gfs::System {
    public:
        virtual void initialize() {
            watchGroups({"enemy"});
        }

        virtual void processEntity(gfs::Entity* entity, const float delta) {
            auto ai = entity->getComponent<AIComponent>();
            ai->nextState();
        }
};
