#include "Component.hpp"

namespace gfs {
    Component::Component():
        id{Component::nextId++} {} 

    Component::~Component() {
    }

    int Component::nextId = 1;
}
