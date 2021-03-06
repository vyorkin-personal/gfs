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
    auto inputSystem = systemManager->add(new InputSystem());

    world.setDelta(1.2);

    SECTION("tag") {
        auto player1 = entityManager->create();
        auto player2 = entityManager->create();
        auto playerState1 = new PlayerStateComponent(120);
        auto playerState2 = new PlayerStateComponent(120);

        player1->setTag("player");
        player1->addComponent(playerState1);
        player2->addComponent(playerState2);

        playerSystem->process();

        auto expectedHealth1 = 119;
        auto expectedHealth2 = 120;
        auto actualHealth1 = playerState1->getHealth();
        auto actualHealth2 = playerState2->getHealth();
        
        REQUIRE(expectedHealth1 == actualHealth1);
        REQUIRE(expectedHealth2 == actualHealth2);
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

        REQUIRE(position->point.x > 1.2f);
        REQUIRE(position->point.y > 3.4f);
    }

    SECTION("event bus") {
        auto eventBus = world.getEventBus();

        auto player = entityManager->create();
        auto velocity = new VelocityComponent(1.0f, 1.0f);
        auto position = new PositionComponent(1.2f, 3.4f);

        player->setTag("player");
        player->addComponent(velocity);
        player->addComponent(position);

        eventBus->emit(KeyDownEvent(13));
        inputSystem->process();

        REQUIRE(velocity->vector.x > 1.4f);
        REQUIRE(velocity->vector.y > 1.4f);
    }
}
