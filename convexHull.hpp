#ifndef convexHull_hpp
#define convexHull_hpp

#include <algorithm>
#include <iostream>

#include "util.hpp"

namespace geo
{
template <typename T>
int convexHull(const    std::vector<Point2_<T> >& points,
	std::vector<Edge2_<T> >&  edges)
{
	std::vector<Point2_<T>> P = points;
	std::sort(P.begin(), P.end());

	for (auto point : P)
	{
		std::cout << point.x << " " << point.y << std::endl;
	}

	return 0;
}
}

#endif /* convexHull_hpp */
