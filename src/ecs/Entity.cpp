#include "ecs/Entity.hpp"
#include "ecs/World.hpp"

namespace gfs {
    namespace ecs {
        Entity::Entity(World* world, const int id) {
            this->world = world;
            this->id = id;

            this->entityManager = world->getEntityManager();
            this->uidRegistry = world->getUidRegistry();
            this->tagManager = world->getTagManager();
            this->groupManager = world->getGroupManager();
        }

        void Entity::addComponent(Component* component) {
            entityManager->addComponent(this, component);
        }

        void Entity::addComponents(const ComponentSet& componentSet) {
            entityManager->addComponents(this, componentSet);
        }

        void Entity::addComponents(var<Component*> components) {
            addComponents(ComponentSet(components));
        }

        void Entity::removeComponents() {
            entityManager->removeComponents(this);
        }

        void Entity::removeComponent(const Uid& uid) {
            entityManager->removeComponent(this, uid);
        }

        Component* Entity::getComponent(const Uid& uid) {
            return entityManager->getComponent(this, uid);
        }

        ComponentSet Entity::getComponents() {
            return entityManager->getComponents(this);
        }

        void Entity::reset() {
            bits = EntityBits{};
        }

        void Entity::destroy() {
            world->destroyEntity(this);
        }

        StringSet Entity::getGroups() {
            return groupManager->getGroupsContaining(this);
        }

        void Entity::addToGroup(const String& group) {
            groupManager->addToGroup(this, group);
            entityManager->notifyEntityChanged(this);
        }

        void Entity::addToGroups(var<String> groups) {
            addToGroups(StringSet(groups));
        }

        void Entity::addToGroups(const StringSet& groups) {
            for (const auto& group: groups)
                groupManager->addToGroup(this, group);
            entityManager->notifyEntityChanged(this);
        }

        void Entity::removeFromGroup(const String& group) {
            groupManager->removeFromGroup(this, group);
            entityManager->notifyEntityChanged(this);
        }

        bool Entity::isInGroup(const String& group) {
            return groupManager->isInGroup(this, group);
        }

        void Entity::clearGroups() {
            groupManager->clear(this);
            entityManager->notifyEntityChanged(this);
        }

        String Entity::getTag() {
            return tagManager->get(this);
        }

        void Entity::setTag(const String& tag) {
            tagManager->set(this, tag);
            entityManager->notifyEntityChanged(this);
        }

        bool Entity::hasTag() {
            return tagManager->isSet(this);
        }

        void Entity::clearTag() {
            tagManager->clear(this);
            entityManager->notifyEntityChanged(this);
        }

        String Entity::toString() const {
            std::ostringstream oss;
            oss << "[Entity(id: " << id << ")]" << std::endl;
            return oss.str();
        }
    }
}
