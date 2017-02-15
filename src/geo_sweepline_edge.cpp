#include "geo_sweepline_edge.hpp"
#include <limits>


using namespace geo;

bool SweepLineEdge::operator< (const SweepLineEdge& edge) const
{
	double y = *ref_y;

	double x1 = getSortValue(y);
	double x2 = edge.getSortValue(y);

	return  x1 < x2 ? true : false;
}


double SweepLineEdge::getSortValue(double y) const
{
	// get the minimum x vertex
	Vector2 min = v0->point;
	if (v1->point.x < v0->point.x)
	{
		min = v1->point;
	}

	// check for a horizontal line
	if (slope_inverse == std::numeric_limits<double>::infinity()) {
		// for horizontal lines, use the min x
		return min.x;
	}
	
	// otherwise compute the intersection point
	return min.x + (y - min.y) * slope_inverse;
}