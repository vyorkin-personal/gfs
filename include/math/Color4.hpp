#pragma once

#include "Prerequisites.hpp"

namespace gfs {
    namespace math {
	template <class T>
	struct Color4 {
	    static const Color4<T> Black;
	    static const Color4<T> White;
	    static const Color4<T> Red;
	    static const Color4<T> Green;
	    static const Color4<T> Blue;
	    static const Color4<T> Alpha;

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
