#include "catch.hpp"

#include "World.hpp"
#include "SystemManager.hpp"

using namespace gfs;

TEST_CASE("SystemManager") {
    auto world = World();
    auto systemManager = world.getSystemManager();
}
