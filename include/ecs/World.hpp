#pragma once

#include "Prerequisites.hpp"
#include "UidRegistry.hpp"
#include "EntityManager.hpp"
#include "Entity.hpp"
#include "SystemManager.hpp"
#include "TagManager.hpp"
#include "GroupManager.hpp"

namespace gfs {
    namespace ecs {
        class World {
            public:
                World();
                ~World();

                UidRegistry* getUidRegistry() const {
                    return uidRegistry;
                }

                SystemManager* getSystemManager() const {
                    return systemManager;
                }

                EntityManager* getEntityManager() const {
                    return entityManager;
                }

                TagManager* getTagManager() const {
                    return tagManager;
                }

                GroupManager* getGroupManager() const {
                    return groupManager;
                }

                Entity* createEntity();
                void destroyEntity(Entity* entity);
                Entity* getEntity(const int entityId);

                void process();

                void setDelta(const double dt) {
                    delta = dt;
                }

                double getDelta() const {
                    return delta;
                }

            private:
                UidRegistry* uidRegistry;
                SystemManager* systemManager;
                EntityManager* entityManager;
                TagManager* tagManager;
                GroupManager* groupManager;

                EntitySet destroyedEntities;

                double delta;
        };
    }
}
