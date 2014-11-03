#pragma once

#include "Prerequisites.hpp"

namespace gfs {
    class TagManager {
        public:
            void set(Entity* entity, const String& tag);

            void clear(const String& tag);
            void clear(Entity* entity);

            bool isSet(const String& tag);
            bool isSet(Entity* entity);

            Entity* get(const String& tag);
            String get(Entity* entity);

        private:
            TagEntityMap entityByTag;
            EntityTagMap tagByEntity;
    };
}
