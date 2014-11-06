#include "ecs/System.hpp"
#include "ecs/Entity.hpp"

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

        void System::process(const float delta) {
            if (!onProcessing()) return;

            for (auto& entity: entities)
                processEntity(entity, delta);

            onProcessed();
        }

        bool System::isWatchingFor(Entity* entity) const {
            return (entity->getSystemBits() & bits.system) == bits.system;
        }

        bool System::isInterestedIn(Entity* entity) const {
            return bits.contains(entity->getBits());
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

        void System::add(Entity* entity) {
            entities.insert(entity);
            entity->addSystemBit(bits.system);
            onAdded(entity);
        }

        void System::remove(Entity* entity) {
            entities.erase(entity);
            entity->removeSystemBit(bits.system);
            onRemoved(entity);
        }
    }
}
