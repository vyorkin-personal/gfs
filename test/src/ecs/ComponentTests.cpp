#include "catch.hpp"
#include "Test.hpp"

TEST_CASE("Component") {
    auto p1 = PositionComponent(1.1f, 1.2f);
    auto p2 = PositionComponent(2.1f, 2.2f);

    SECTION("every new components gets a unique id") {
	REQUIRE_FALSE(p1.getId() == p2.getId());
    }

    SECTION("equality") {
	REQUIRE(p1 == p1);
	REQUIRE_FALSE(p1 == p2);
    }
}
