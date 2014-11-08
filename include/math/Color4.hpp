#pragma once

#include "Prerequisites.hpp"

namespace gfs {
    namespace math {
	template <class T>
	struct Color4 {
	    static const Color4<T> black;
	    static const Color4<T> white;
	    static const Color4<T> red;
	    static const Color4<T> green;
	    static const Color4<T> blue;
	    static const Color4<T> alpha;

	    Color4() = default;
	    Color4(const T r, const T g, const T b);
	    Color4(const T r, const T g, const T b, const T a);

	    bool operator == (const Color4& other) const;
	    bool operator != (const Color4& other) const;

	    T r, g, b, a;
	};
    }
}

#include "math/Color4.inl"
