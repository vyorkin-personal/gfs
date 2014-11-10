#pragma once

#include "examples/Example.hpp"
#include "examples/event/KeyDownEvent.hpp"

class InputSystem: public System {
    public:
        virtual void initialize() override {
            watchTags({"player"});
            getEventBus()->subscribe<KeyDownEvent>(this, &InputSystem::onKeyDown);
        }

        void onKeyDown(const KeyDownEvent& e) {
            if (e.keyCode != 13) return;

            for (auto& entity: getEntities()) {
                auto velocity = entity->getComponent<VelocityComponent>();
                velocity->vector += 0.5f;
            }
        }
};
