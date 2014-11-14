#pragma once

#include "Prerequisites.hpp"
#include "Uid.hpp"
#include "UidRegistry.hpp"

namespace gfs {
    namespace ecs {
        class GroupManager {
            public:
                GroupManager(UidRegistry* uidRegistry);

                void addToGroup(Entity* entity, const String& group);
                void removeFromGroup(Entity* entity, const String& group);

                void clear(Entity* entity);
                void clear(const String& group);

                bool isInAnyGroup(Entity* entity) const;
                bool isInGroup(Entity* entity, const String& group) const;

                StringSet getGroupsContaining(Entity* entity) const;
                EntitySet getEntitiesInGroup(const String& group) const;

                void reset();

            private:
                UidRegistry* uidRegistry;
                GroupMap groupsByEntity;
                EntitiesByGroupMap entitiesByGroup;
        };
    }
}
