#pragma once

#include "Prerequisites.hpp"

namespace gfs {
    class GroupManager {
        public:
            void addToGroup(Entity* entity, const String& group);

            void removeFromGroup(Entity* entity, const String& group);
            void clearGroups(Entity* entity);

            bool isInAnyGroup(Entity* entity) const;
            bool isInGroup(Entity* entity, const String& group) const;

            StringSet getGroupsContaining(Entity* entity) const;
            EntitySet getEntitiesInGroup(const String& group) const;

        private:
            GroupMap groupsByEntity;
            EntitiesByGroupMap entitiesByGroup;
    };
}
