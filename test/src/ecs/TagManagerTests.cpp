#include "catch.hpp"
#include "Test.hpp"

TEST_CASE("TagManager") {
    auto world = World();
    auto tagManager = world.getTagManager();
    auto entityManager = world.getEntityManager();

    SECTION("set") {
        auto entity = entityManager->create();
        entity->setTag("test");
    }
}
