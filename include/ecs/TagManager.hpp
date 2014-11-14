#pragma once

#include "Prerequisites.hpp"
#include "Uid.hpp"
#include "UidRegistry.hpp"

namespace gfs {
    namespace ecs {
        class TagManager {
            public:
                TagManager(UidRegistry* uidRegistry);

                void set(Entity* entity, const String& tag);

                void clear(const String& tag);
                void clear(Entity* entity);
                void clear(const int entityId);

                bool isSet(const String& tag);
                bool isSet(Entity* entity);

                Entity* get(const String& tag);
                String get(Entity* entity);

                void reset();

            private:
                UidRegistry* uidRegistry;
                TagEntityMap entityByTag;
                EntityTagMap tagByEntity;
        };
    }
}
