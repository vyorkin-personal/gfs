#include "GroupManager.hpp"
#include "Entity.hpp"

namespace gfs {
    void GroupManager::addToGroup(Entity* entity, const String& group) {
        auto it = entitiesByGroup.insert(std::make_pair(group, EntitySet()));

        it.first->second.insert(entity);
        groupsByEntity.insert(std::make_pair(entity->getId(), group));
    }

    void GroupManager::removeFromGroup(Entity* entity, const String& group) {
        const auto it = entitiesByGroup.find(group);
        if (it != entitiesByGroup.cend())
            it->second.erase(entity);

        auto range = groupsByEntity.equal_range(entity->getId());
        auto next = range.first;
        const auto end = range.second;

        if (next != groupsByEntity.end()) {
            while (next != end) {
                if (next->second == group) {
                    next = groupsByEntity.erase(next);
                } else {
                    next++;
                }
            }
        }
    }

    void GroupManager::clearGroups(Entity* entity) {
        auto groups = getGroupsContaining(entity);
        if (groups.empty()) return;

        for (const auto& group: groups) {
            const auto it = entitiesByGroup.find(group);
            if (it != entitiesByGroup.cend())
                it->second.erase(entity);
        }

        groupsByEntity.erase(entity->getId());
    }

    bool GroupManager::isInAnyGroup(Entity* entity) const {
        auto range = groupsByEntity.equal_range(entity->getId());
        return (range.first != groupsByEntity.cend());
    }

    bool GroupManager::isInGroup(Entity* entity, const String& group) const {
        auto const it = entitiesByGroup.find(group);
        return it != entitiesByGroup.cend() &&
            it->second.find(entity) != it->second.cend();
    }

    StringSet GroupManager::getGroupsContaining(Entity* entity) const {
        auto result = StringSet();

        auto range = groupsByEntity.equal_range(entity->getId());

        auto next = range.first;
        const auto end = range.second;

        if (next != groupsByEntity.cend()) {
            while (next != end) {
                result.insert(next->second);
                next++;
            }
        }

        return result;
    }

    EntitySet GroupManager::getEntitiesInGroup(const String& group) const {
        const auto it = entitiesByGroup.find(group);
        return it == entitiesByGroup.cend() ?  EntitySet() : it->second;
    }
}
