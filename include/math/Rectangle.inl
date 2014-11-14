namespace gfs {
    namespace math {
	template <class T>
	Rectangle<T>::Rectangle(const Point2<T>& leftBottom, const Point2<T>& rightTop):
	    leftBottom{leftBottom}, rightTop{rightTop} {}

	template <class T>
	Rectangle<T>::Rectangle(const T x1, const T y1, const T x2, const T y2):
	    leftBottom{Point2<T>(x1, y1)}, rightTop{Point2<T>(x2, y2)} {}
    }
}
