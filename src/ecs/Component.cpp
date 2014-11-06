#include "ecs/Component.hpp"

namespace gfs {
    namespace ecs {
        Component::Component():
            id{Component::nextId++} {} 

        Component::~Component() {
        }

        int Component::nextId = 1;
    }
}
