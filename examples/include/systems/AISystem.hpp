#pragma once

#include "Example.hpp"
#include "components/AIComponent.hpp"

class AISystem: public ecs::System {
    public:
        virtual void initialize() {
            watchGroups({"enemy"});
        }

        virtual void processEntity(ecs::Entity* entity, const float delta) {
            auto ai = entity->getComponent<AIComponent>();
            ai->nextState();
        }
};
