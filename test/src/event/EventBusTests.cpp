#include "catch.hpp"
#include "Test.hpp"

TEST_CASE("EventBus") {
	auto uidRegistry = new UidRegistry();
	auto eventBus = EventBus(uidRegistry);
	
	int marker = 1;
	auto eventListener = EventListener(eventBus, &marker);

	SECTION("subscribe and emit") {
		eventBus.emit(ExplosionEvent(10.0f));

		REQUIRE(marker == 2);
	}
}
