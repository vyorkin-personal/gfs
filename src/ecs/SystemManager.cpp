#include "ecs/SystemManager.hpp"
#include "ecs/World.hpp"

namespace gfs {
    namespace ecs {
        SystemManager::SystemManager(World* world):
            world{world} {
            uidRegistry = world->getUidRegistry();
            eventBus = world->getEventBus();
        }

        SystemManager::~SystemManager() {
            for (auto& it: systems)
                delete it.second;

            systems.clear();
        }

        void SystemManager::process() {
            for (const auto& it: systems)
                it.second->process();
        }

        SystemSet SystemManager::getSystems() const {
            auto result = SystemSet();
            std::transform(systems.begin(), systems.end(),
                std::inserter(result, result.begin()),
                [](const std::pair<Uid, System*>& key_value) {
                    return key_value.second;
                });

            return result;
        }

        void SystemManager::reset() {
            for (auto& it: systems) {
                const auto uid = it.first;
                auto system = it.second;

                system->reset();
                system->bits.system = uid.getBit();
                system->initialize();
            }
        }
    }
}
