#include "catch.hpp"
#include "Test.hpp"

TEST_CASE("System") {
    auto world = World();
    auto systemManager = world.getSystemManager();
    auto entityManager = world.getEntityManager();
    auto dumper = EntityManagerDumper(entityManager);

    auto movementSystem = systemManager->create<MovementSystem>();
    auto playerSystem = systemManager->create<PlayerSystem>();
    auto aiSystem = systemManager->create<AISystem>();

    world.setDelta(1.2);

    SECTION("tag") {
        auto player = entityManager->create();
        auto playerState = new PlayerStateComponent(120);

        player->setTag("player");
        player->addComponent(playerState);

        playerSystem->process(world.getDelta());

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

        aiSystem->process(world.getDelta());

        REQUIRE_FALSE(ai1->isIdling());
        REQUIRE_FALSE(ai2->isIdling());
    }

    SECTION("component") {
        auto ship = entityManager->create();
        auto velocity = new VelocityComponent(1.0F, 1.0F);
        auto position = new PositionComponent(1.2F, 3.4F);

        ship->addComponent(velocity);
        ship->addComponent(position);

        movementSystem->process(world.getDelta());

        REQUIRE(position->getX() > 1.2);
        REQUIRE(position->getY() > 3.4);
    }
}
