#pragma once

#include "Prerequisites.hpp"
#include "UidRegistry.hpp"
#include "EntityBits.hpp"

namespace gfs {
    class System {
        public:
            virtual ~System() = default;

            virtual void initialize() = 0;
            void process(const float delta);

            void onChange(Entity* entity);

        protected:
            template<class... Components>
            void watchComponents() {
                addToComponentBits(TypeList<Components...>());
            }
            void watchComponents(var<std::type_info> types);
            void watchTags(var<String> tags);
            void watchGroups(var<String> groups);

            virtual void processEntity(Entity* entity, const float delta) = 0;

            virtual bool onProcessing() { return true; }
            virtual void onProcessed() {}

            virtual void onRemoved(Entity* entity) {}
            virtual void onAdded(Entity* entity) {}

            EntitySet::size_type getEntityCount() const;

        private:
            UidRegistry* uidRegistry;

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
