#include "ecs/System.hpp"
#include "ecs/Entity.hpp"
#include "ecs/World.hpp"

namespace gfs {
    namespace ecs {
        void System::onChange(Entity* entity) {
            const bool watching = isWatchingFor(entity);
            const bool interested = isInterestedIn(entity);

            if (interested && !watching)
                add(entity);
            else if (watching && !interested)
                remove(entity);
        }

        void System::process() {
            if (!onProcessing()) return;

            for (auto& entity: entities)
                processEntity(entity);

            onProcessed();
        }

        bool System::isWatchingFor(Entity* entity) const {
            return (entity->bits.system & bits.system) == bits.system;
        }

        bool System::isInterestedIn(Entity* entity) const {
            return bits.contains(entity->bits);
        }

        void System::watchComponents(var<std::type_info> types) {
            for (const auto& type: types)
                bits.component |= uidRegistry->getBit(type);
        }

        void System::watchTags(var<String> tags) {
            for (const auto& tag: tags)
                bits.tag |= uidRegistry->getBit(tag);
        }

        void System::watchGroups(var<String> groups) {
            for (const auto& group: groups)
                bits.group |= uidRegistry->getBit(group);
        }

        EntitySet::size_type System::getEntityCount() const {
            return entities.size();
        }

        double System::getDelta() const {
            return world->getDelta();
        }

        void System::reset() {
            bits.reset();

            for (auto& entity: entities)
                entity->bits.system.reset();

            entities.clear();
        }

        void System::add(Entity* entity) {
            entities.insert(entity);
            entity->bits.system |= bits.system;
            onAdded(entity);
        }

        void System::remove(Entity* entity) {
            entities.erase(entity);
            entity->bits.system &= ~bits.system;
            onRemoved(entity);
        }
    }
}
