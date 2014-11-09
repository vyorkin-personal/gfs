#pragma once

#include "Prerequisites.hpp"
#include "Uid.hpp"
#include "UidRegistry.hpp"

namespace gfs {
    namespace ecs {
        class EntityManager final {
            public:
                EntityManager(World* world);
                ~EntityManager();

                Entity* create();

                void destroy(Entity* entity);
                void destroyAll();

                Entity* get(const int entityId) {
                    return activeEntities[entityId];
                }

                void addComponent(Entity* entity, Component* component);
                void addComponents(Entity* entity, const ComponentSet& componentSet);

                void removeComponents(Entity* entity);
                void removeComponent(Entity* entity, const Uid& uid);
                template<class C> void removeComponent(Entity* entity) {
                    auto uid = uidRegistry->get<C>();
                    removeComponent(entity, uid);
                }

                ComponentSet getComponents(Entity* entity);
                Component* getComponent(Entity* entity, const Uid& uid);
                template<class C> C* getComponent(Entity* entity) {
                    auto uid = uidRegistry->get<C>();
                    return dynamic_cast<C*>(getComponent(entity, uid));
                }

                void notifyEntityChanged(Entity* entity);

                bool isActive(Entity* entity) const;
                bool isActive(const int id) const;

                IdEntityMap::size_type getTotalActive() const;

                long getTotalCreated() const {
                    return totalCreated;
                }

                long getTotalDestroyed() const {
                    return totalDestroyed;
                }

            private:
                Entity* create(const int id);

                void addEntityComponent(Entity* entity, Component* component);
                IdEntityMap::iterator destroyEntity(Entity* entity);

                void removeComponentFromEntityComponents(const int entityId, const Uid& uid);
                void removeComponentFromComponentLookup(const int entityId, const Uid& uid);

                void freeEntityPool();

                World* world;
                SystemManager* systemManager;
                UidRegistry* uidRegistry;

                int nextEntityId;
                long nextUniqueEntityId;

                long totalCreated;
                long totalDestroyed;

                IdEntityMap activeEntities;
                EntityQueue entityPool;

                EntityComponentMap entityComponents;
                ComponentLookupMap componentLookup;

                friend EntityManagerDumper;
        };
    }
}
