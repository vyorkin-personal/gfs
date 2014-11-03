#include "catch.hpp"
#include "Component.hpp"

using namespace gfs;

#include "components/PositionComponent.hpp"

TEST_CASE("Component") {
    auto p1 = PositionComponent(1.1F, 1.2F);
    auto p2 = PositionComponent(2.1F, 2.2F);

    SECTION("every new components gets a unique id") {
	REQUIRE_FALSE(p1.getId() == p2.getId());
    }

    SECTION("equality") {
	REQUIRE(p1 == p1);
	REQUIRE_FALSE(p1 == p2);
    }
}
