#ifndef GEO_SWEEPLINE_EDGE_HPP
#define GEO_SWEEPLINE_EDGE_HPP
#include "geo_sweepline_vertex.hpp"

namespace geo
{

class SweepLineEdge
{
	// The current state of the sweepline. This value is 
	// shared by all edges when sorted in a binary search
	// tree.
	double* ref_y;

public:

	// The left-top vertex of the line segment
	SweepLineVertex* v0 = nullptr;

	// The bottom-right vertex of the line segment
	SweepLineVertex* v1 = nullptr;

	// The helper of this edge
	SweepLineVertex* helper = nullptr;

	// The inverted slope of the edge.
	// This value will be inf when the line segment is horizontal
	double slope_inverse;

	SweepLineEdge(double* ref_y)
		: ref_y(ref_y)
	{};

	double getSortValue(double y) const;

	bool operator< (const SweepLineEdge& edge) const;

};




} // namespace geo

#endif /* GEO_SWEEPLINE_EDGE_HPP */