#pragma once

#include "Prerequisites.hpp"
#include "math/Vector2.hpp"

namespace gfs {
    namespace math {
	template <class T>
	struct Rectangle {
	    Rectangle(const Point2<T>& leftBottom, const Point2<T>& rightTop);
	    Rectangle(const T x1, const T y1, const T x2, const T y2);
	    Rectangle(const Rectangle&) = default;

	    Point2<T> leftBottom;
	    Point2<T> rightTop;
	};
    }
}

#include "math/Rectangle.inl"
