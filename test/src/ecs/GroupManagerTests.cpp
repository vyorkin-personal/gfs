#include "catch.hpp"
#include "Test.hpp"

TEST_CASE("GroupManager") {
    auto world = World();

    auto entityManager = world.getEntityManager();
    auto groupManager = world.getGroupManager();

    auto entity1 = entityManager->create();
    auto entity2 = entityManager->create();
    auto entity3 = entityManager->create();
    auto entity4 = entityManager->create();

    const auto group1 = String("group1");
    const auto group2 = String("group2");

    groupManager->addToGroup(entity1, group1);
    groupManager->addToGroup(entity2, group1);
    groupManager->addToGroup(entity2, group2);
    groupManager->addToGroup(entity3, group2);

    SECTION("is in group") {
        REQUIRE(groupManager->isInGroup(entity1, group1));
        REQUIRE(groupManager->isInGroup(entity2, group1));
        REQUIRE_FALSE(groupManager->isInGroup(entity3, group1));

        REQUIRE_FALSE(groupManager->isInGroup(entity1, group2));
        REQUIRE(groupManager->isInGroup(entity2, group2));
        REQUIRE(groupManager->isInGroup(entity3, group2));
    }

    SECTION("is in any group") {
        REQUIRE(groupManager->isInAnyGroup(entity1));
        REQUIRE_FALSE(groupManager->isInAnyGroup(entity4));
    }

    SECTION("get groups containing entity") {
        auto entity1Groups = groupManager->getGroupsContaining(entity1);
        auto entity2Groups = groupManager->getGroupsContaining(entity2);

        auto expectedEntity1Groups = StringSet{group1};
        auto expectedEntity2Groups = StringSet{group1, group2};

        REQUIRE(entity1Groups == expectedEntity1Groups); 
        REQUIRE(entity2Groups == expectedEntity2Groups); 
    }


    SECTION("get entities in group") {
        auto group1Entities = groupManager->getEntitiesInGroup(group1);
        auto group2Entities = groupManager->getEntitiesInGroup(group2);

        auto expectedGroup1Entities = EntitySet{entity1, entity2}; 
        auto expectedGroup2Entities = EntitySet{entity2, entity3}; 

        REQUIRE(expectedGroup1Entities == group1Entities);
        REQUIRE(expectedGroup2Entities == group2Entities);
    }

    SECTION("remove from group") {
        groupManager->removeFromGroup(entity2, group1);
        
        REQUIRE_FALSE(groupManager->isInGroup(entity2, group1));
        REQUIRE(groupManager->isInGroup(entity2, group2));
    }

    SECTION("clear by entity") {
        groupManager->clear(entity2);
        
        REQUIRE_FALSE(groupManager->isInGroup(entity2, group1));
        REQUIRE_FALSE(groupManager->isInGroup(entity2, group2));
        REQUIRE(groupManager->isInGroup(entity1, group1));
    }

    SECTION("isEmptyGroup") {
        groupManager->removeFromGroup(entity1, group1);
        groupManager->removeFromGroup(entity2, group1);

        REQUIRE(groupManager->isEmptyGroup(group1));
    }
}
