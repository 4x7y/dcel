#ifndef GEO_SWEEPLINE_STATE_HPP
#define GEO_SWEEPLINE_STATE_HPP

#include <queue>
#include "geo_dcel.hpp"
#include "geo_sweepline_vertex.hpp"
#include "geo_rbtree.hpp"

namespace geo
{
class Compare
{
public:
	bool less(SweepLineVertex* vertex, SweepLineEdge * edge) const;
	bool less(SweepLineEdge* edge, SweepLineVertex* vertex) const;
	bool less(SweepLineEdge* e1, SweepLineEdge* e2) const;
};

class SweepLineState
{
public:
	DoubleEdgeList*			dcel;
	double					reference_y;
	RBTree<SweepLineEdge *, SweepLineVertex *, Compare> tree;

	SweepLineState() = default;
	
	void initialize(
		const std::vector<Vector2>& points,
		std::priority_queue<SweepLineVertexPtr>& queue);

private:
	bool isBelow(
		const Vector2& point1,
		const Vector2& point2) const;

	SweepLineVertexType getType(
		const Vector2& point_left,
		const Vector2& point,
		const Vector2& point_right) const;
};
}

#endif /* GEO_SWEEPLINE_STATE_HPP */