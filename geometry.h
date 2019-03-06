#ifndef GEOMETRY_H
#define GEOMETRY_H
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

/**
	@brief Computes the convex hull of a set of points (Graham scan)
	Returns a list containing the vertices of the convex hull in clockwise order
**/
template <typename T>
std::list<Point2D<T>> compute_convex_hull(std::set<Point2D<T>, lex<T>> set) {

	// Upper convex hull

	std::list<Point2D<T>> l_upper;
	typename std::set<Point2D<T>, lex<T>>::iterator set_it = set.begin();
	// Insert the first two points of the set and move iterator to the third
	l_upper.push_back(*set_it);
	++set_it;
	l_upper.push_back(*set_it);

	for(unsigned int i = 3; i < set.size()+1; ++i){
		++set_it;
		l_upper.push_back(*set_it);

		#ifndef NDEBUG
		std::cout<<"1. Initial upper hull: ";
		for (typename std::list<Point2D<T>>::iterator it=l_upper.begin(); it!=l_upper.end(); ++it)
			std::cout << ' ' << *it;
		std::cout<<"\n";
		#endif

		int orientation = -1;

		do{
			typename std::list<Point2D<T>>::iterator r_it = l_upper.end();
			typename std::list<Point2D<T>>::iterator middle;

			--r_it;
			Point2D<T> c = *r_it;
			--r_it;
			middle = r_it;
			Point2D<T> b = *middle;
			--r_it;
			Point2D<T> a = *r_it;

			orientation = compute_orientation(a, b, c);
			if(orientation != 2)
				l_upper.erase(middle);

			#ifndef NDEBUG
			std::cout<<"2. Orientation: " << orientation << "\n";
			std::cout<<"3. Current upper hull: ";
			for (typename std::list<Point2D<T>>::iterator it=l_upper.begin(); it!=l_upper.end(); ++it)
				std::cout << ' ' << *it;
			std::cout<<"\n";
			#endif

		}while(l_upper.size() > 2 && orientation != 2);
	}
	
	#ifndef NDEBUG
	std::cout<<"Upper hull: ";
    for (typename std::list<Point2D<T>>::iterator it=l_upper.begin(); it!=l_upper.end(); ++it)
	    std::cout << ' ' << *it;
	std::cout<<"\n";
    std::cout << "Size: " << l_upper.size() << "\n";
	#endif


	// Lower convex hull

	std::list<Point2D<T>> l_lower;
	typename std::set<Point2D<T>, lex<T>>::reverse_iterator r_set_it = set.rbegin();
	// Insert the last two points of the set and move iterator to the third
	l_lower.push_back(*r_set_it);
	++r_set_it;
	l_lower.push_back(*r_set_it);

	for(unsigned int i = set.size() - 2; i > 0; --i){		
		++r_set_it;
		l_lower.push_back(*r_set_it);

		#ifndef NDEBUG
		std::cout<<"1. Initial lower hull: ";
		for (typename std::list<Point2D<T>>::iterator it=l_lower.begin(); it!=l_lower.end(); ++it)
			std::cout << ' ' << *it;
		std::cout<<"\n";
		#endif

		int orientation = -1;

		do{
			typename std::list<Point2D<T>>::iterator r_it = l_lower.end();
			typename std::list<Point2D<T>>::iterator middle;

			--r_it;
			Point2D<T> c = *r_it;
			--r_it;
			middle = r_it;
			Point2D<T> b = *middle;
			--r_it;
			Point2D<T> a = *r_it;

			orientation = compute_orientation(a, b, c);
			if(orientation != 2)
				l_lower.erase(middle);

			#ifndef NDEBUG
			std::cout<<"2. Orientation: " << orientation << "\n";
			std::cout<<"3. Current lower hull: ";
			for (typename std::list<Point2D<T>>::iterator it=l_lower.begin(); it!=l_lower.end(); ++it)
				std::cout << ' ' << *it;
			std::cout<<"\n";
			#endif

		}while(l_lower.size() > 2 && orientation != 2);
	}
	
	#ifndef NDEBUG
	std::cout<<"Lower hull: ";
    for (typename std::list<Point2D<T>>::iterator it=l_lower.begin(); it!=l_lower.end(); ++it)
	    std::cout << ' ' << *it;
	std::cout<<"\n";
    std::cout << "Size: " << l_lower.size() << "\n";
	#endif

	// Remove first and last elements of l_lower to avoid duplication of the points where l_lower meets l_upper
	l_lower.pop_front();
	l_lower.pop_back();

	// Merge
	l_upper.splice(l_upper.end(), l_lower);
	return l_upper;
}



#endif