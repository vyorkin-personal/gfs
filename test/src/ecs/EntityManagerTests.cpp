#include "catch.hpp"
#include "Test.hpp"

TEST_CASE("EntityManager") {
    auto world = World();
    auto uidRegistry = world.getUidRegistry();
    auto entityManager = world.getEntityManager();

    auto entity1 = entityManager->create();
    auto entity2 = entityManager->create();

    SECTION("every new entity gets a unique id") {
	REQUIRE_FALSE(entity1->getId() == entity2->getId());
    }

    SECTION("equality") {
	REQUIRE(*entity1 == *entity1);
	REQUIRE_FALSE(*entity1 == *entity2);
    }

    SECTION("get entity by id") {
	auto entityId = entity1->getId();
	auto entity = entityManager->get(entityId);

	REQUIRE(*entity == *entity1);
    }

    SECTION("entity destruction makes it inactive") {
	entityManager->destroy(entity2);

	REQUIRE(entityManager->isActive(entity1) == true);
	REQUIRE(entityManager->isActive(entity1->getId()) == true);
	REQUIRE(entityManager->isActive(entity2) == false);
	REQUIRE(entityManager->isActive(entity2->getId()) == false);
    }

    SECTION("totals are correct") {
	auto entity3 = entityManager->create();
	auto entity4 = entityManager->create();
	entityManager->destroy(entity3);

	REQUIRE(entityManager->getTotalCreated() == 4);
	REQUIRE(entityManager->getTotalDestroyed() == 1);
	REQUIRE(entityManager->getTotalActive() == 3);

	entityManager->destroyAll();

	REQUIRE(entityManager->getTotalCreated() == 4);
	REQUIRE(entityManager->getTotalDestroyed() == 4);
	REQUIRE(entityManager->getTotalActive() == 0);
    }

    SECTION("components") {
	auto posUid = uidRegistry->get<PositionComponent>();
	auto velUid = uidRegistry->get<VelocityComponent>();

	auto pos1 = new PositionComponent(1.0f, 2.0f);
	auto pos2 = new PositionComponent(3.0f, 4.0f);

	auto vel1 = new VelocityComponent(2.3f, 1.4f);
	auto vel2 = new VelocityComponent(1.5f, 7.5f);

	entityManager->addComponent(entity1, pos1);
	entityManager->addComponent(entity1, vel1);

	auto entity2Components = ComponentSet{pos2, vel2};
	entityManager->addComponents(entity2, entity2Components);

	SECTION("get by entity") {
	    auto components1 = entityManager->getComponents(entity1);
	    auto components2 = entityManager->getComponents(entity2);

	    SECTION("component count is correct") {
		REQUIRE(components1.size() == 2);
		REQUIRE(components2.size() == 2);
	    }
	    SECTION("components are correct") {
		REQUIRE(components2 == entity2Components);
	    }
	}

	SECTION("has component") {
	    auto entity3 = entityManager->create();
	    auto entity4 = entityManager->create();

	    entityManager->addComponent(entity3, new PositionComponent(1.0f, 2.0f));
	    entityManager->addComponent(entity4, new VelocityComponent(2.0f, 3.0f));

	    REQUIRE(entityManager->hasComponent<PositionComponent>(entity3));
	    REQUIRE_FALSE(entityManager->hasComponent<VelocityComponent>(entity3));

	    REQUIRE_FALSE(entityManager->hasComponent<PositionComponent>(entity4));
	    REQUIRE(entityManager->hasComponent<VelocityComponent>(entity4));
	}

	SECTION("get by entity and component type") {
	    SECTION("components are correct") {
		REQUIRE(entityManager->getComponent(entity1, posUid) == pos1);
		REQUIRE(entityManager->getComponent(entity1, velUid) == vel1);
		REQUIRE(entityManager->getComponent<PositionComponent>(entity1) == pos1);
		REQUIRE(entityManager->getComponent<VelocityComponent>(entity1) == vel1);

		REQUIRE(entityManager->getComponent(entity2, posUid) == pos2);
		REQUIRE(entityManager->getComponent(entity2, velUid) == vel2);
		REQUIRE(entityManager->getComponent<PositionComponent>(entity2) == pos2);
		REQUIRE(entityManager->getComponent<VelocityComponent>(entity2) == vel2);
	    }
	}

	SECTION("remove all entity components") {
	    entityManager->removeComponents(entity1);
	    auto components = entityManager->getComponents(entity1);

	    SECTION("component count is correct") {
		REQUIRE(components.size() == 0);
	    }
	}

	SECTION("remove entity component by type") {
	    entityManager->removeComponent<VelocityComponent>(entity1);
	    auto components = entityManager->getComponents(entity1);

	    SECTION("component count is correct") {
		REQUIRE(components.size() == 1);
	    }
	}
    }
}
