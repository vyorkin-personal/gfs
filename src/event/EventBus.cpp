#include "event/EventBus.hpp"

namespace gfs {
    namespace event {
        EventBus::EventBus(UidRegistry* uidRegistry):
            uidRegistry{uidRegistry} {}
    }
}
