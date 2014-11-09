#pragma once

#include "examples/Example.hpp"
#include "examples/ecs/components/AIComponent.hpp"

class AISystem: public System {
    public:
        virtual void initialize() override {
            watchGroups({"enemy"});
        }

        virtual void processEntity(Entity* entity) override {
            auto ai = entity->getComponent<AIComponent>();
            ai->nextState();
        }
};
