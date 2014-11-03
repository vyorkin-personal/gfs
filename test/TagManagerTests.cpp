#include "catch.hpp"

#include "World.hpp"
#include "TagManager.hpp"

using namespace gfs;

TEST_CASE("TagManager") {
    auto world = World();
    auto tagManager = world.getTagManager();
}
