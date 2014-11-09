#pragma once

#include "examples/Example.hpp"
#include "examples/ecs/components/RenderableComponent.hpp"

class RenderingSystem: public System {
    public:
        virtual void initialize() override {
            watchComponents<RenderableComponent>();
        }

        virtual void processEntity(Entity* entity) override {
            auto renderable = entity->getComponent<RenderableComponent>();
            renderable->draw();
        }
};
