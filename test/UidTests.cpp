#include "catch.hpp"

#include "Prerequisites.hpp"
#include "Uid.hpp"

using namespace gfs;

TEST_CASE("Uid") {
    auto bitSet = BitSet(1);

    SECTION("construction") {
        auto target = Uid(7, BitSet(13));

        REQUIRE(target.getId() == 7);
        REQUIRE(target.getBit().to_ulong() == 13);
    }

    SECTION("equality operator") {
        auto lhs = Uid(1, bitSet);
        auto rhs = Uid(2, bitSet);

        REQUIRE(lhs == rhs);
    }
}
