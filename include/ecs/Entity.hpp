#pragma once

#include "Prerequisites.hpp"
#include "ecs/Uid.hpp"
#include "ecs/Component.hpp"
#include "ecs/EntityBits.hpp"
#include "ecs/EntityManager.hpp"
#include "ecs/TagManager.hpp"

namespace gfs {
    namespace ecs {
        class Entity final {
            public:
                Entity(World* world, const int id);
                Entity(const Entity&) = delete;
                Entity& operator=(const Entity&) = delete;

                void addComponent(Component* component);
                void addComponents(const ComponentSet& componentSet);
                void addComponents(var<Component*> components);

                void removeComponents();
                void removeComponent(const Uid& uid);
                template<class C> void removeComponent() {
                    entityManager->removeComponent<C>(this);
                }

                ComponentSet getComponents();
                Component* getComponent(const Uid& uid);
                template<class C> C* getComponent() {
                    return entityManager->getComponent<C>(this);
                }

                void destroy();

                StringSet getGroups();
                void addToGroup(const String& group);
                void addToGroups(const StringSet& groups);
                void addToGroups(var<String> groups);
                bool isInGroup(const String& group);
                void removeFromGroup(const String& group);
                void clearGroups();

                String getTag();
                void setTag(const String& tag);
                bool hasTag();
                void clearTag();

                String toString() const;

                int getId() const {
                    return id;
                }

                bool operator == (const Entity& other) const {
                    return getId() == other.getId();
                }

            private:
                void reset();

                const EntityBits& getBits() const {
                    return bits;
                }

                void addComponentBit(const BitSet& bit) {
                    bits.component |= bit;
                }
                void removeComponentBit(const BitSet& bit) {
                    bits.component &= ~bit;
                }

                const BitSet& getSystemBits() const {
                    return bits.system;
                }
                void addSystemBit(const BitSet& bit) {
                    bits.system |= bit;
                }
                void removeSystemBit(const BitSet& bit) {
                    bits.system &= ~bit;
                }

                int id;

                EntityBits bits;

                World* world;
                UidRegistry* uidRegistry;
                EntityManager* entityManager;
                GroupManager* groupManager;
                TagManager* tagManager;

                friend EntityManager;
                friend System;
        };
    }
}
