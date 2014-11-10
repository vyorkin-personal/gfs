#pragma once

#include "Prerequisites.hpp"

#include "UidRegistry.hpp"
#include "event/EventBus.hpp"
#include "ecs/EntityManager.hpp"
#include "ecs/Entity.hpp"
#include "ecs/SystemManager.hpp"
#include "ecs/TagManager.hpp"
#include "ecs/GroupManager.hpp"

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

                event::EventBus* getEventBus() const {
                    return eventBus;
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
                event::EventBus* eventBus;

                EntitySet destroyedEntities;

                double delta;
        };
    }
}
