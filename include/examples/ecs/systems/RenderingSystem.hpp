#pragma once

#include "examples/Example.hpp"
#include "examples/ecs/components/RenderableComponent.hpp"

class RenderingSystem: public System {
    public:
        virtual void initialize() {
            watchComponents<RenderableComponent>();
        }

        virtual void processEntity(Entity* entity, const float delta) {
            auto renderable = entity->getComponent<RenderableComponent>();
            renderable->draw();
        }
};
