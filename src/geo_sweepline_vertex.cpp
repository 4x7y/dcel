#include "geo_sweepline_vertex.hpp"

using namespace geo;

bool SweepLineVertex::operator< (const SweepLineVertex& vertex) const
{
	// sort by the y first then by x if the y's are equal
	Vector2 p = point;
	Vector2 q = vertex.point;
	double diff = q.y - p.y;

	if (diff == 0.0) {
		return p.x < q.x;
	}

	if (diff > 0) {
		return false;
	}

	return true;
}


bool SweepLineVertex::isInteriorRight()
{
	return true;
}