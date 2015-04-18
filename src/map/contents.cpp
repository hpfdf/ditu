#include "contents.h"
#include <cmath>

Point Point3D::GetPoint() const {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

static const double EPS=1e-8;

static Point operator -(const Point &p1, const Point &p2) {
	Point p;
	p.x = p1.x-p2.x;
	p.y = p1.y-p2.y;
	return p;
}

static auto mult(const Point &p1, const Point &p2) -> decltype(p1.x) {
	return p1.x*p2.y - p1.y*p2.x;
}

static auto mult(const Point &p0, const Point &p1, const Point &p2) -> decltype(p1.x) {
	return mult(p1 - p0, p2 - p0);
}

static auto dot(const Point &p1, const Point &p2) -> decltype(p1.x) {
	return p1.x*p2.x + p1.y*p2.y;
}

static auto dot(const Point &p0, const Point &p1, const Point &p2) -> decltype(p1.x) {
	return dot(p1 - p0, p2 - p0);
}

template<class T> static int sgn(T x) {
	if (x < -EPS) return -1;
	if (x > +EPS) return +1;
	return 0;
}

bool GeometryUtils::Cut(const Point &a, const Point &b, const Point &c, const Point &d) {
	if (sgn(mult(a, b, c)) * sgn(mult(a, b, d)) > 0)
		return false;
	if (sgn(mult(c, d, a)) * sgn(mult(c, d, b)) > 0)
		return false;
    return true;
}

static bool OnSegment(const Point &p, const Point &a, const Point &b) {
	return sgn(mult(p, a, b)) == 0 && sgn(dot(p, a, b)) <= 0;
}

bool GeometryUtils::Inside(const Point &p, const Polygon &a) {
	int wn = 0;
	for (int i = 0; i < a.shape.size(); ++i) {
		const Point &a1 = a.shape[i];
		const Point &a2 = a.shape[(i + 1) % a.shape.size()];
		if (OnSegment(p, a1, a2))
			return true;
		int k = sgn(mult(a1, a2, p));
		int d1 = sgn(a1.y - p.y);
		int d2 = sgn(a2.y - p.y);
		if (k > 0 && d1 <= 0 && d2 > 0)
			++wn;
		if (k < 0 && d2 <= 0 && d1 > 0)
			--wn;
	}
	return wn != 0;
}

bool GeometryUtils::Hit(const Polygon &a, const Polygon &b) {
	if (a.shape.size() <= 0 || b.shape.size() <= 0)
		return false; // bad
	if (Inside(a.shape[0], b) || Inside(b.shape[0], a))
		return true;
	for (int i = 0; i < a.shape.size(); ++i) {
		const Point &a1 = a.shape[i];
		const Point &a2 = a.shape[(i + 1) % a.shape.size()];
		for (int j = 0; j < b.shape.size(); ++j) {
			const Point &b1 = b.shape[j];
			const Point &b2 = b.shape[(j + 1) % b.shape.size()];
			if (Cut(a1, a2, b1, b2))
				return true;
		}
	}
    return false;
}

static auto dist(const Point &p1, const Point &p2) -> decltype(p1.x) {
	#define ___sqr(x) (x)*(x)
	return (decltype(p1.x))sqrt(___sqr(p1.x - p2.x) + ___sqr(p1.y - p2.y));
	#undef ___sqr
}

float GeometryUtils::Length(const JsonObjectList<Point> &route) {
	float ans = 0;
	for (int i = 1; i < route.size(); ++i)
		ans += dist(route[i - 1], route[i]);
	return ans;
}

