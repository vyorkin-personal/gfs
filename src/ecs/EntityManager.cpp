#include "ecs/EntityManager.hpp"
#include "ecs/Entity.hpp"
#include "ecs/World.hpp"
#include "ecs/System.hpp"

namespace gfs {
   namespace ecs {
      EntityManager::EntityManager(World* w):
      world{w}, nextEntityId{0}, totalCreated{0}, totalDestroyed{0} {
         uidRegistry = world->getUidRegistry();
         systemManager = world->getSystemManager();
      }

      EntityManager::~EntityManager() {
         destroyAll();
         freeEntityPool();

         uidRegistry = nullptr;
         systemManager = nullptr;
         world = nullptr;
      }

      Entity* EntityManager::create() {
         return create(nextEntityId++);
      }

      Entity* EntityManager::create(const int id) {
         Entity* entity = nullptr;

         if (!entityPool.empty()) {
               entity = entityPool.front();
               entity->id = id;

               entityPool.pop();
         } else {
               entity = new Entity(world, id);
         }

         activeEntities.insert(std::make_pair(id, entity));
         totalCreated++;

         return entity;
      }

      void EntityManager::destroy(Entity* entity) {
         destroyEntity(entity);
      }

      void EntityManager::destroyAll() {
         for (auto it = activeEntities.begin(); it != activeEntities.end();)
               it = destroyEntity(it->second);
      }

      void EntityManager::freeEntityPool() {
         while (!entityPool.empty()) {
               delete entityPool.front();
               entityPool.pop();
         }
      }

      IdEntityMap::iterator EntityManager::destroyEntity(Entity* entity) {
         auto entityId = entity->getId();

         const auto it = activeEntities.find(entityId);
         if (it == activeEntities.cend()) return it;

         auto next = activeEntities.erase(it);
         removeComponents(entity);
         entity->reset();
         entityPool.push(entity);
         totalDestroyed++;
         notifyEntityChanged(entity);

         return next;
      }

      void EntityManager::addComponent(Entity* entity, Component* component) {
         addEntityComponent(entity, component);
         notifyEntityChanged(entity);
      }

      void EntityManager::addComponents(Entity* entity, const ComponentSet& components) {
         for (auto& it: components)
               addEntityComponent(entity, it);
         notifyEntityChanged(entity);
      }

      void EntityManager::addEntityComponent(Entity* entity, Component* component) {
         auto entityId = entity->getId();
         auto uid = uidRegistry->get(typeid(*component));
         auto it = componentLookup.insert(std::make_pair(uid, ComponentMap()));

         it.first->second.insert(std::make_pair(entityId, component));
         entityComponents.insert(std::make_pair(entityId, component));

         entity->addComponentBit(uid.getBit());
      }

      void EntityManager::removeComponents(Entity* entity) {
         auto entityId = entity->getId();

         for (auto& iter : componentLookup) {
               const auto it = iter.second.find(entityId);
               if (it != iter.second.cend()) {
                  auto component = it->second;
                  auto uid = uidRegistry->get(typeid(*component));        
                  removeComponent(entity, uid);
               }
         }
      }

      void EntityManager::removeComponentFromEntityComponents(const int entityId, const Uid& uid) {
         auto range = entityComponents.equal_range(entityId);
         if (range.first == entityComponents.cend()) return;

         auto next = range.first;
         const auto end = range.second;

         while (next != end) {
               Component* target = next->second;
               auto type = uidRegistry->get(typeid(*target));

               if (uid == Uid::None || type == uid) {
                  next = entityComponents.erase(next);
               } else {
                  next++;
               }
         }
      }

      void EntityManager::removeComponentFromComponentLookup(const int entityId, const Uid& uid) {
         const auto iter = componentLookup.find(uid);
         if (iter == componentLookup.end()) return;

         const auto it = iter->second.find(entityId);
         if (it != iter->second.cend()) {
               delete it->second;
               iter->second.erase(it);
         }
      }

      void EntityManager::removeComponent(Entity* entity, const Uid& uid) {
         auto entityId = entity->getId();

         removeComponentFromEntityComponents(entityId, uid);
         removeComponentFromComponentLookup(entityId, uid);

         entity->removeComponentBit(uid.getBit());

         notifyEntityChanged(entity);
      }

      ComponentSet EntityManager::getComponents(Entity* entity) {
         auto entityId = entity->getId();
         auto result = ComponentSet();

         auto range = entityComponents.equal_range(entityId);

         auto next = range.first;
         const auto end = range.second;

         if (next != entityComponents.cend()) {
               while (next != end) {
                  result.insert(next->second);
                  next++;
               }
         }

         return result;
      }

      Component* EntityManager::getComponent(Entity* entity, const Uid& uid) {
         const auto iter = componentLookup.find(uid);
         if (iter == componentLookup.cend()) return nullptr;

         auto entityId = entity->getId();
         const auto it = iter->second.find(entityId);

         return it == iter->second.cend() ? nullptr : it->second;
      }

      bool EntityManager::isActive(Entity* entity) const {
         return isActive(entity->getId());
      }

      bool EntityManager::isActive(const int id) const {
         return activeEntities.find(id) != activeEntities.cend();
      }

      IdEntityMap::size_type EntityManager::getTotalActive() const {
         return activeEntities.size();
      }

      void EntityManager::notifyEntityChanged(Entity* entity) {
         auto systems = systemManager->getSystems();
         for (auto& system : systems) {
               system->onChange(entity);
         }
      }
   }
}
