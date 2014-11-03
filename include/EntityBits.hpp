#pragma once

#include "Prerequisites.hpp"

namespace gfs {
    class EntityBits {
        public:
            BitSet system;
            BitSet tag;
            BitSet group;
            BitSet component;

            bool contains(const EntityBits& bits) const {
                return
                    (bits.tag & tag) == tag ||
                    (bits.group & group) == group ||
                    (bits.component & component) == component;
            }
    };
}
