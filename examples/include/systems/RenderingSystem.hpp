#pragma once

#include "Example.hpp"
#include "components/RenderableComponent.hpp"

class RenderingSystem: public ecs::System {
    public:
        virtual void initialize() {
            watchComponents<RenderableComponent>();
        }

        virtual void processEntity(ecs::Entity* entity, const float delta) {
            auto renderable = entity->getComponent<RenderableComponent>();
            renderable->draw();
        }
};
