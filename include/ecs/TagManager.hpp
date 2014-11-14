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

                bool isSet(const String& tag);
                bool isSet(Entity* entity);

                Entity* get(const String& tag);
                String get(Entity* entity);

            private:
                UidRegistry* uidRegistry;
                TagEntityMap entityByTag;
                EntityTagMap tagByEntity;
        };
    }
}
