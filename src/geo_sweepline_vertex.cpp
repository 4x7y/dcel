#include "geo_sweepline_vertex.hpp"
#include "geo_sweepline_edge.hpp"

using namespace geo;

bool SweepLineVertex::operator< (const SweepLineVertex& vertex) const
{
	// sort by the y first then by x if the y's are equal
	Vector2 p = point;
	Vector2 q = vertex.point;
	double diff = q.y - p.y;

	// If the two vertex have the same y coordinate
	if (this->point.y == vertex.point.y)
	{
		// The left vertex is larger
		return this->point.x > vertex.point.x;
	}

	// The higher vertex is larger
	if (this->point.y < vertex.point.y) {
		return true;
	}

	return false;
}


bool SweepLineVertex::isInteriorRight() const
{
	return left->isInteriorRight();
}