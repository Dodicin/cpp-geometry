#ifndef UTILS_H
#define UTILS_H
#include <cmath>
#include <ostream>
#include <set>
#include <list>

#ifndef NDEBUG
#include <iostream>
#endif

/**
	@brief 2D Point class
	Represents a bidimensional T point
**/
template <typename T>
struct Point2D{
	T x;
  	T y;
	Point2D() {}
  	Point2D(T x1, T y1) : x(x1), y(y1) {}
	Point2D(const Point2D &other) : x(other.x), y(other.y) {}
    ~Point2D() {}
};

template <typename T>
std::ostream& operator<< (std::ostream &os, const Point2D<T> &p){
	os << "<" << p.x << "," << p.y << ">";
	return os;
}

/**
	@brief Functor to check the lexicographic relation between two points
	@param Point2D a
	@param Point2D b
	@return boolean true if a is greater than b
**/
template <typename T>
struct lex {
	bool operator()(const Point2D<T> &a, const Point2D<T> &b) const {
		bool flag = false;
		if(a.x < b.x) flag = true;
		else if(a.x == b.x)
			if(a.y < b.y) flag = true;

		return flag;
	}
};


/**
	@brief Euclidean distance function
	Computes Euclidean distance between two points
**/
template <typename T>
double e_dist(Point2D<T> a, Point2D<T> b){
	double dx = b.x - a.x;
	double dy = b.y - a.y;
	return sqrt(dx + dy);
}

/**
	@brief Manhattan distance function
	Computes Manhattan distance between two points
**/
template <typename T>
double m_dist(Point2D<T> a, Point2D<T> b){
	int dx = b.x - a.x;
	int dy = b.y - a.y;
	return abs(dx) + abs(dy);
}

/**
	@brief Orientation of an ordered triplet of points
	Returns the orientation of a triplet of points by comparing their slope:
	2 = Clockwise
	1 = Counterclockwise
	0 = Collinear
**/
template <typename T>
int compute_orientation(Point2D<T> a, Point2D<T> b, Point2D<T> c){
	int val = (b.y - a.y)*(c.x - b.x) - (c.y - b.y)*(b.x - a.x);

	if(val == 0) return 0;
	return (val > 0) ? 2 : 1;
}

/**
	@brief Finds if a point lies on a segment
	Given two points p and q, returns if a point m lies on the segment pq
**/
template <typename T>
bool on_segment(Point2D<T> p, Point2D<T> q, Point2D<T> m){
	if(m.x <= max(p.x, q.x) && m.x >= min(p.x, q.x) &&
	   m.y <= max(p.y, q.y) && m.y >= min(p.y, q.y))
	    return true;
	else
		return false;
}

/**
	@brief Intersection between two segments
	Returns if two segments intersect by checking the orientation of triplets of points
**/
template <typename T>
bool seg_intersect(Point2D<T> p1, Point2D<T> q1, Point2D<T> p2, Point2D<T> q2){
	int o1 = compute_orientation(p1, q1, p2);
	int o2 = compute_orientation(p1, q1, q2);
	int o3 = compute_orientation(p2, q2, p1);
	int o4 = compute_orientation(p2, q2, q1);

	// General case
	if(o1 != o2 && o3 != o4) return true;

	// Collinear segments cases
	if(o1 == 0 && on_segment(p1, q1, p2)) return true;
	if(o2 == 0 && on_segment(p1, q1, q2)) return true;
	if(o3 == 0 && on_segment(p2, q2, p1)) return true;
	if(o4 == 0 && on_segment(p2, q2, q1)) return true;

	return false;
}

#endif