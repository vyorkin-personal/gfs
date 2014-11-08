namespace gfs {
    namespace math {
	template <class T> const Color4<T> Color4<T>::black = Color4(0, 0, 0, 0);
	template <class T> const Color4<T> Color4<T>::white = Color4(1, 1, 1, 0);
	template <class T> const Color4<T> Color4<T>::red = Color4(1, 0, 0);
	template <class T> const Color4<T> Color4<T>::green = Color4(0, 1, 0);
	template <class T> const Color4<T> Color4<T>::blue = Color4(0, 0, 1);
	template <class T> const Color4<T> Color4<T>::alpha = Color4(0, 0, 0, 1);

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
