#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include "utils.h"

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

	// Merge upper and lower convex hulls
	l_upper.splice(l_upper.end(), l_lower);
	return l_upper;
}


#endif