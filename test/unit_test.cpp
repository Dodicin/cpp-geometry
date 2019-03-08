#include "voronoi.h"
#include "convex_hull.h"
#include "utils.h"
#include <iostream>
#include <random>

void test_orientation(){
    std::cout << std::endl << "***Orientation test START***" << std::endl << std::endl;

    Point2D<int> a = Point2D<int>(0, 0);
    Point2D<int> b = Point2D<int>(0, 3);
    Point2D<int> c = Point2D<int>(1, 1);

    std::cout << "Orientation: " << compute_orientation(a, b, c) << std::endl;
    std::cout << std::endl << "***Orientation test END***" << std::endl << std::endl;

}

void test_convex_hull(){
    std::cout << std::endl << "***Convex Hull test START***" << std::endl << std::endl;

    typedef Point2D<int> Point2D;
    std::set<Point2D, lex<int>> t;
    std::list<Point2D> ch;

    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> dist(-100, 100);

    for(unsigned int i=0; i<50; ++i)
        t.insert(Point2D(dist(gen), dist(gen)));

    // t.insert(Point2D(0, 3));
    // t.insert(Point2D(1, 1));
    // t.insert(Point2D(2, 2));
    // t.insert(Point2D(4, 4));
    // t.insert(Point2D(0, 0));
    // t.insert(Point2D(1, 2));
    // t.insert(Point2D(3, 1));
    // t.insert(Point2D(3, 3));

    std::cout<<"Point2D set: ";
	for (std::set<Point2D>::iterator it=t.begin(); it!=t.end(); ++it)
	    std::cout << ' ' << *it;
	std::cout<<"\n";
    std::cout << "Size: " << t.size() << std::endl;
    
    ch = compute_convex_hull(t);

    std::cout<<"Convex hull: ";
    for (std::list<Point2D>::iterator it=ch.begin(); it!=ch.end(); ++it)
	    std::cout << ' ' << *it;
	std::cout<<"\n";
    std::cout << "Size: " << ch.size() << std::endl;

    std::cout << std::endl << "***Convex Hull test END***" << std::endl << std::endl;

}

int main(){

    test_orientation();

    test_convex_hull();

    return 0;
}