#include "ecs/TagManager.hpp"
#include "ecs/Entity.hpp"

namespace gfs {
    namespace ecs {
        void TagManager::set(Entity* entity, const String& tag) {
            entityByTag.insert(std::make_pair(tag, entity));
            tagByEntity.insert(std::make_pair(entity->getId(), tag));
        }

        void TagManager::clear(const String& tag) {
            const auto it = entityByTag.find(tag);
            if (it != entityByTag.cend()) {
                tagByEntity.erase(it->second->getId());
                entityByTag.erase(it);
            }
        }

        void TagManager::clear(Entity* entity) {
            const auto it = tagByEntity.find(entity->getId()); 
            if (it != tagByEntity.cend()) {
                entityByTag.erase(it->second);
                tagByEntity.erase(it);
            }
        }

        bool TagManager::isSet(const String& tag) {
            return entityByTag.find(tag) != entityByTag.cend();
        }

        bool TagManager::isSet(Entity* entity) {
            return tagByEntity.find(entity->getId()) != tagByEntity.cend();
        }

        Entity* TagManager::get(const String& tag) {
            const auto it = entityByTag.find(tag);
            return it == entityByTag.cend() ? nullptr : it->second;
        }

        String TagManager::get(Entity* entity) {
            const auto it = tagByEntity.find(entity->getId());
            return it == tagByEntity.cend() ? nullptr : it->second;
        }
    }
}
