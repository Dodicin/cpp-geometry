#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <cmath.h>

/**
	@brief Point class
	Represents a bidimensional T point
**/
template <typename T>
class Point{
	T _x;
  	T _y;
	Point() {}
  	Point(T x, T y) : _x(x), _y(y) {}
    
    T const& x() const;
    T const& y() const;
};


/**
	@brief Euclidean distance function
	Computes Euclidean distance between two points
**/
double e_dist(Point<int> a, Point<int> b){
	double dx = b.x - a.x;
	double dy = b.y - a.y;
	return sqrt(dx + dy);
}

/**
	@brief Manhattan distance function
	Computes Manhattan distance between two points
**/
double m_dist(Point<int> a, Point<int> b){
	int dx = b.x - a.x;
	int dy = b.y - a.y;
	return abs(dx) + abs(dy);
}
#endif