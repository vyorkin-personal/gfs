#include "ecs/GroupManager.hpp"
#include "ecs/Entity.hpp"

namespace gfs {
    namespace ecs {
        GroupManager::GroupManager(UidRegistry* uidRegistry):
            uidRegistry{uidRegistry} {}

        void GroupManager::addToGroup(Entity* entity, const String& group) {
            const auto uid = uidRegistry->get(group);
            auto it = entitiesByGroup.insert(std::make_pair(uid, EntitySet()));

            it.first->second.insert(entity);

            groupsByEntity.insert(std::make_pair(entity->getId(), group));
            entity->bits.group |= uid.getBit();
        }

        void GroupManager::removeFromGroup(Entity* entity, const String& group) {
            const auto uid = uidRegistry->get(group);
            const auto it = entitiesByGroup.find(uid);
            if (it == entitiesByGroup.cend()) return;

            it->second.erase(entity);

            auto range = groupsByEntity.equal_range(entity->getId());
            auto next = range.first;
            const auto end = range.second;

            if (next != groupsByEntity.end()) {
                while (next != end) {
                    if (next->second == group) {
                        entity->bits.group &= ~uid.getBit();
                        next = groupsByEntity.erase(next);
                    } else {
                        next++;
                    }
                }
            }
        }

        void GroupManager::clear(Entity* entity) {
            entity->bits.group.reset();
            auto groups = getGroupsContaining(entity);
            if (groups.empty()) return;

            for (const auto& group: groups) {
                const auto uid = uidRegistry->get(group);
                const auto it = entitiesByGroup.find(uid);
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
            const auto uid = uidRegistry->get(group); 
            const auto it = entitiesByGroup.find(uid);
            return it != entitiesByGroup.cend() &&
                it->second.find(entity) != it->second.cend();
        }

        bool GroupManager::isEmptyGroup(const String& group) const {
            const auto uid = uidRegistry->get(group);
            auto it = entitiesByGroup.find(uid);
            return it == entitiesByGroup.cend() || it->second.empty();
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
            const auto uid = uidRegistry->get(group);
            const auto it = entitiesByGroup.find(uid);
            return it == entitiesByGroup.cend() ?  EntitySet() : it->second;
        }

        void GroupManager::reset() {
            for (auto& it: entitiesByGroup) {
                for (auto& entity: it.second)
                    entity->bits.group.reset();
            }

            groupsByEntity.clear();
            entitiesByGroup.clear();
        }
    }
}
