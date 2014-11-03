#include "catch.hpp"

#include "World.hpp"
#include "EntityManager.hpp"
#include "EntityManagerDumper.hpp"
#include "Entity.hpp"

#include "components/PositionComponent.hpp"
#include "components/VelocityComponent.hpp"

using namespace gfs;

TEST_CASE("Entity") {
    auto world = World();
    auto uidRegistry = world.getUidRegistry();
    auto entityManager = world.getEntityManager();

    auto entity = entityManager->create();

    SECTION("add multiple components at once") {
        auto pos = new PositionComponent(1.1F, 2.1F);
        auto vel = new VelocityComponent(2.2F, 3.2F);

        entity->addComponents({pos, vel});

        REQUIRE(entity->getComponent<PositionComponent>() == pos);
        REQUIRE(entity->getComponent<VelocityComponent>() == vel);
    }

    SECTION("group") {
        SECTION("addToGroup") {
            entity->addToGroup("group1");
            
            REQUIRE(entity->isInGroup("group1"));
        }

        SECTION("addToGroups") {
            entity->addToGroups({"group1", "group2"});
            auto groups = entity->getGroups();

            REQUIRE(groups.find("group1") != groups.cend());
            REQUIRE(groups.find("group2") != groups.cend());

            SECTION("removeFromGroup") {
                entity->removeFromGroup("group2");

                REQUIRE(entity->isInGroup("group1"));
                REQUIRE_FALSE(entity->isInGroup("group2"));
            }
        }


        SECTION("clearGroups") {
            entity->addToGroups({"group1", "group2"});
            entity->clearGroups();

            auto groups = entity->getGroups();

            REQUIRE(groups.empty());
        }
    }

    SECTION("tag") {
        SECTION("setTag") {
        }

        SECTION("clearTag") {
        }
    }
}
