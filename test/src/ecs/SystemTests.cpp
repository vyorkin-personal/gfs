#include "catch.hpp"
#include "Test.hpp"

TEST_CASE("System") {
    auto world = World();
    auto systemManager = world.getSystemManager();
    auto entityManager = world.getEntityManager();
    auto dumper = EntityManagerDumper(entityManager);

    auto movementSystem = systemManager->add(new MovementSystem());
    auto playerSystem = systemManager->add(new PlayerSystem());
    auto aiSystem = systemManager->add(new AISystem());

    world.setDelta(1.2);

    SECTION("tag") {
        auto player = entityManager->create();
        auto playerState = new PlayerStateComponent(120);

        player->setTag("player");
        player->addComponent(playerState);

        playerSystem->process();

        auto expectedHealth = 119;
        auto actualHealth = playerState->getHealth();
        
        REQUIRE(expectedHealth == actualHealth);
    }

    SECTION("group") {
        auto enemy1 = entityManager->create();
        auto enemy2 = entityManager->create();
        auto ai1 = new AIComponent();
        auto ai2 = new AIComponent();

        enemy1->addToGroup("enemy");
        enemy2->addToGroup("enemy");

        enemy1->addComponent(ai1);
        enemy2->addComponent(ai2);
        
        REQUIRE(ai1->isIdling());
        REQUIRE(ai2->isIdling());

        aiSystem->process();

        REQUIRE_FALSE(ai1->isIdling());
        REQUIRE_FALSE(ai2->isIdling());
    }

    SECTION("component") {
        auto ship = entityManager->create();
        auto velocity = new VelocityComponent(1.0f, 1.0f);
        auto position = new PositionComponent(1.2f, 3.4f);

        ship->addComponent(velocity);
        ship->addComponent(position);

        movementSystem->process();

        REQUIRE(position->point.x > 1.2);
        REQUIRE(position->point.y > 3.4);
    }
}
