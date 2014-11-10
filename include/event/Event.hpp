#pragma once

#include "Prerequisites.hpp"

namespace gfs {
    namespace event {
        struct Event {
            virtual ~Event() = default;
        };
    }
}
