#pragma once

#include "Prerequisites.hpp"
#include "math/Vector2.hpp"

namespace gfs {
    namespace math {
	struct Polygon {
	    Polygon(const Polygon& other) {
		vertices = other.vertices;
	    }
	    std::vector<Vector2f> vertices;
	};
    }
}
