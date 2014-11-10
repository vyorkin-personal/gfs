#include "catch.hpp"
#include "Test.hpp"

TEST_CASE("EventBus") {
	auto uidRegistry = new UidRegistry();
	auto eventBus = EventBus(uidRegistry);
	auto eventListener = EventListener(eventBus);
	auto explosionEvent = ExplosionEvent(10.0f);

	SECTION("subscribe and emit") {
		eventBus.emit(explosionEvent);

		REQUIRE(explosionEvent.finished == true);
	}
}
