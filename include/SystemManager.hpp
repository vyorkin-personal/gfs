#pragma once

#include "Prerequisites.hpp"
#include "UidRegistry.hpp"
#include "System.hpp"

namespace gfs {
    class SystemManager final {
        public:
            SystemManager(UidRegistry* registry);
            ~SystemManager();

            SystemSet getSystems() const;
            void process(const float delta);

            template<class S> S* create() {
                const auto uid = uidRegistry->get<S>();

                auto system = new S();
                system->uidRegistry = uidRegistry;
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

        private:
            UidRegistry* uidRegistry;
            SystemMap systems;
    };
}
