#pragma once

#include "Prerequisites.hpp"
#include "UidRegistry.hpp"
#include "ecs/EntityBits.hpp"

namespace gfs {
    namespace ecs {
        class System {
            public:
                virtual ~System() = default;

                void process();
                void onChange(Entity* entity);

                virtual void initialize() = 0;
                virtual void processEntity(Entity* entity) {};

            protected:
                template<class... Components>
                void watchComponents() {
                    addToComponentBits(TypeList<Components...>());
                }
                void watchComponents(var<std::type_info> types);
                void watchTags(var<String> tags);
                void watchGroups(var<String> groups);

                event::EventBus* getEventBus() const {
                    return eventBus;
                }

                EntitySet& getEntities() {
                    return entities;
                }
                
                EntitySet::size_type getEntityCount() const;

                double getDelta() const;

                virtual bool onProcessing() { return true; }
                virtual void onProcessed() {}

                virtual void onRemoved(Entity* entity) {}
                virtual void onAdded(Entity* entity) {}

            private:
                World* world;
                UidRegistry* uidRegistry;
                event::EventBus* eventBus;

                EntitySet entities;
                EntityBits bits;

                bool isWatchingFor(Entity* entity) const;
                bool isInterestedIn(Entity* entity) const;

                void add(Entity* entity);
                void remove(Entity* entity);

                template<class...> struct TypeList {};

                template<class C, class... Rest>
                void addToComponentBits(TypeList<C, Rest...>) {
                    bits.component |= uidRegistry->getBit<C>();
                    addToComponentBits(TypeList<Rest...>());
                }

                void addToComponentBits(TypeList<>) {}

                friend SystemManager;
        };
    }
}
