#include "ecs/Component.hpp"

namespace gfs {
    namespace ecs {
        Component::Component():
            id{Component::nextId++} {} 

        int Component::nextId = 1;
    }
}
