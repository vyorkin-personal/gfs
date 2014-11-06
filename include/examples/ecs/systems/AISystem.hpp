#pragma once

#include "examples/Example.hpp"
#include "examples/ecs/components/AIComponent.hpp"

class AISystem: public System {
    public:
        virtual void initialize() {
            watchGroups({"enemy"});
        }

        virtual void processEntity(Entity* entity) {
            auto ai = entity->getComponent<AIComponent>();
            ai->nextState();
        }
};
