#ifndef GEO_CONVEX_HULL_HPP
#define GEO_CONVEX_HULL_HPP

#include <algorithm>
#include <iostream>
#include <vector>

#include "geo_type.hpp"

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

#endif /* GEO_CONVEX_HULL_HPP */
