#include "catch.hpp"
#include "Test.hpp"

TEST_CASE("SystemManager") {
    auto world = World();
    auto systemManager = world.getSystemManager();
}
