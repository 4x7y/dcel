#include "geo_sweepline_edge.hpp"


using namespace geo;

bool SweepLineEdge::operator< (const SweepLineEdge& edge) const
{
	return this->getX() < edge.getX() ? true : false;
}


double SweepLineEdge::getX() const
{
	return -(B * ref_y + C) / A;
}

void SweepLineEdge::setReferenceY(double y)
{
	ref_y = y;
}
