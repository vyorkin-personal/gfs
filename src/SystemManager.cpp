#include "SystemManager.hpp"

namespace gfs {
    SystemManager::SystemManager(UidRegistry* registry):
        uidRegistry{registry} {}

    SystemManager::~SystemManager() {
        for (auto& it: systems)
            delete it.second;

        systems.clear();
    }

    void SystemManager::process(const float delta) {
        for (auto& it: systems)
            it.second->process(delta);
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
}
