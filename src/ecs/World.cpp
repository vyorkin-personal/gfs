#include "ecs/World.hpp"

namespace gfs {
    namespace ecs {
        World::World(): delta(0.0) {
            uidRegistry = new UidRegistry();
            eventBus = new event::EventBus(uidRegistry);
            systemManager = new SystemManager(this);
            entityManager = new EntityManager(this);
            groupManager = new GroupManager(uidRegistry);
            tagManager = new TagManager(uidRegistry);
        }

        World::~World() {
            delete tagManager;
            delete groupManager;
            delete entityManager;
            delete systemManager;
            delete eventBus;
            delete uidRegistry;
        }

        Entity* World::getEntity(const int entityId) {
            return entityManager->get(entityId);
        }

        Entity* World::createEntity() {
            return entityManager->create();
        }

        void World::destroyEntity(Entity* entity) {
            destroyedEntities.insert(entity);
        }

        void World::process() {
            systemManager->process();

            for (auto& entity: destroyedEntities) {
                groupManager->clear(entity);
                tagManager->clear(entity);
                entityManager->destroy(entity);
            }

            destroyedEntities.clear();
        }

        void World::reset() {
            // TODO: Fix it
            /* tagManager->reset(); */
            /* groupManager->reset(); */
            entityManager->destroyAll();
        }
    }
}
