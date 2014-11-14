#pragma once

#include "Prerequisites.hpp"
#include "UidRegistry.hpp"
#include "event/EventBus.hpp"
#include "ecs/System.hpp"
#include "ecs/World.hpp"

namespace gfs {
    namespace ecs {
        class SystemManager final {
            public:
                SystemManager(World* world);
                ~SystemManager();

                SystemSet getSystems() const;
                void process();

                template<class S> S* add(S* system) {
                    const auto uid = uidRegistry->get<S>();

                    system->world = world;
                    system->uidRegistry = uidRegistry;
                    system->eventBus = eventBus;
                    system->bits.system = uid.getBit();

                    system->initialize();

                    systems.insert(std::make_pair(uid, system));

                    return system;
                }

                template<class S> S* get() const {
                    const auto uid = uidRegistry->get<S>();
                    auto it = systems.find(uid);

                    return it == systems.cend() ?
                        nullptr : dynamic_cast<S*>(it->second);
                }

                void reset();

            private:
                World* world;
                UidRegistry* uidRegistry;
                event::EventBus* eventBus;
                SystemMap systems;
        };
    }
}
