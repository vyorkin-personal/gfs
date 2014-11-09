namespace gfs {
    namespace math {
	template <class T> const Color4<T> Color4<T>::Black = Color4(0, 0, 0, 0);
	template <class T> const Color4<T> Color4<T>::White = Color4(1, 1, 1, 0);
	template <class T> const Color4<T> Color4<T>::Red = Color4(1, 0, 0);
	template <class T> const Color4<T> Color4<T>::Green = Color4(0, 1, 0);
	template <class T> const Color4<T> Color4<T>::Blue = Color4(0, 0, 1);
	template <class T> const Color4<T> Color4<T>::Alpha = Color4(0, 0, 0, 1);

	template <class T>
	Color4<T>::Color4(const T r, const T g, const T b):
	    r{r}, g{b}, b{b}, a{0} {}

	template <class T>
	Color4<T>::Color4(const T r, const T g, const T b, const T a):
	    r{r}, g{b}, b{b}, a{a} {}

	template <class T>
	bool Color4<T>::operator == (const Color4& other) const {
	    return r == other.r && g == other.g && b == other.b && a == other.a;
	}

	template <class T>
	bool Color4<T>::operator != (const Color4& other) const {
	    return !(*this == other);
	}
    }
}
