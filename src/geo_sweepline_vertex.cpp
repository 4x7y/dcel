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

static double getLocation(Vector2 point, Vector2 linePoint1, Vector2 linePoint2) {
	return (linePoint2.x - linePoint1.x) * (point.y - linePoint1.y) -
		(point.x - linePoint1.x) * (linePoint2.y - linePoint1.y);
}

bool SweepLineVertex::isLeft(const SweepLineEdge* edge) const
{
	// its in between the min and max x so we need to 
	// do a side of line test
	double location = getLocation(point, edge->v0->point, edge->v1->point);
	if (location < 0.0) {
		return true;
	}
	else {
		return false;
	}
}