#pragma once

#include "System.hpp"

#include "components/RenderableComponent.hpp"

class RenderingSystem: public gfs::System {
    public:
        virtual void initialize() {
            watchComponents<RenderableComponent>();
        }

        virtual void processEntity(gfs::Entity* entity, const float delta) {
            auto renderable = entity->getComponent<RenderableComponent>();
            renderable->draw();
        }
};
