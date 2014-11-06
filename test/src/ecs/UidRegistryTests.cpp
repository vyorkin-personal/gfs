#include "catch.hpp"
#include "Test.hpp"

TEST_CASE("UidRegistry") {
    auto registry = UidRegistry();

    SECTION("get") {
	auto str1 = String("><(((*>");
	auto str2 = String("<*)))><");

	auto vec2 = std::vector<int>{4, 5, 6};
	auto vec1 = std::vector<int>{1, 2, 3};

	auto pos1 = new PositionComponent(1.0f, 2.0f);
	auto pos2 = new PositionComponent(2.0f, 3.0f);

	auto vel1 = new VelocityComponent(1.2f, 3.4f);
	auto vel2 = new VelocityComponent(5.6f, 7.8f);

	auto uidStr1Type = registry.get(typeid(str1));
	auto uidStr2Type = registry.get(typeid(str2));
	auto uidStrType = registry.get<String>();

	auto uidVec1 = registry.get(typeid(vec1));
	auto uidVec2 = registry.get(typeid(vec2));
	auto uidVec = registry.get<std::vector<int>>();

	auto uidPos1 = registry.get(typeid(*pos1));
	auto uidPos2 = registry.get(typeid(*pos2));
	auto uidPos = registry.get<PositionComponent>();

	auto uidVel1 = registry.get(typeid(*vel1));
	auto uidVel2 = registry.get(typeid(*vel2));
	auto typeVel = registry.get<VelocityComponent>();

	SECTION("uids of String") {
	    auto str3 = String("><(((*>");
	    auto str4 = String("<*)))><");

	    auto uidStr1 = registry.get(str1);
	    auto uidStr2 = registry.get(str2);
	    auto uidStr3 = registry.get(str3);
	    auto uidStr4 = registry.get(str4);

	    SECTION("uids of the same string are equal") {
		REQUIRE(uidStr1 == uidStr3);
		REQUIRE(uidStr2 == uidStr4);
	    }

	    SECTION("uids of different strings are not equal") {
		REQUIRE_FALSE(uidStr1 == uidStr4);
		REQUIRE_FALSE(uidStr2 == uidStr3);
	    }
	}

	SECTION("uids of the same type are equal") {
	    REQUIRE(uidStr1Type == uidStr2Type);
	    REQUIRE(uidStr1Type == uidStrType);
	    REQUIRE(uidStr2Type == uidStrType);

	    REQUIRE(uidVec1 == uidVec2);
	    REQUIRE(uidVec1 == uidVec);
	    REQUIRE(uidVec2 == uidVec);

	    REQUIRE(uidPos1 == uidPos2);
	    REQUIRE(uidPos1 == uidPos);
	    REQUIRE(uidPos2 == uidPos);

	    REQUIRE(uidVel1 == uidVel2);
	    REQUIRE(uidVel1 == typeVel);
	    REQUIRE(uidVel2 == typeVel);
	}

	SECTION("uids of different types are not equal") {
	    REQUIRE_FALSE(uidStr1Type == uidVec1);
	    REQUIRE_FALSE(uidStr2Type == uidVec2);
	    REQUIRE_FALSE(uidStrType == uidVec);
	}
    }
}
