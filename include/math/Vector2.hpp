#pragma once

#include "Prerequisites.hpp"

namespace gfs {
    namespace math {
	template <class T>
	struct Vector2 {
	    static const Vector2 Zero;
	    static const Vector2 One;

	    Vector2() = default;
	    Vector2(const Vector2&) = default;
	    Vector2(const T x, const T y);

	    T distance(const Vector2& other) const;
	    T distanceSquared(const Vector2& other) const;

	    T dot(const Vector2& other) const;
	    T cross(const Vector2& other) const;

	    void normalize();

	    T direction() const;

	    T length() const;
	    T lengthSquared() const;

	    Vector2& rotate(const T angle);

	    bool operator == (const Vector2& other) const;
	    bool operator != (const Vector2& other) const;

	    Vector2 operator - () const;

	    Vector2 operator + (const Vector2& other) const;
	    Vector2 operator - (const Vector2& other) const;
	    Vector2 operator * (const Vector2& other) const;
	    Vector2 operator / (const Vector2& other) const;

	    Vector2 operator + (const T value) const;
	    Vector2 operator - (const T value) const;
	    Vector2 operator * (const T value) const;
	    Vector2 operator / (const T value) const;

	    Vector2& operator += (const T value);
	    Vector2& operator -= (const T value);
	    Vector2& operator *= (const T value);
	    Vector2& operator /= (const T value);

	    Vector2& operator += (const Vector2& other);
	    Vector2& operator -= (const Vector2& other);
	    Vector2& operator *= (const Vector2& other);
	    Vector2& operator /= (const Vector2& other);

	    T x, y;
	};
    }
}

#include "math/Vector2.inl"
