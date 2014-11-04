#include "World.hpp"

namespace gfs {
    World::World(): delta(0.0) {
        uidRegistry = new UidRegistry();
        systemManager = new SystemManager(uidRegistry);
        entityManager = new EntityManager(this);
        groupManager = new GroupManager();
        tagManager = new TagManager();
    }

    World::~World() {
        delete tagManager;
        delete groupManager;
        delete entityManager;
        delete systemManager;
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
        systemManager->process(delta);

        for (auto& entity: destroyedEntities) {
            groupManager->clearGroups(entity);
            tagManager->clear(entity);
            entityManager->destroy(entity);
        }

        destroyedEntities.clear();
    }
}
