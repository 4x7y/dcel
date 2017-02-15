#ifndef GEO_SWEEPLINE_STATE_HPP
#define GEO_SWEEPLINE_STATE_HPP

#include <queue>
#include "geo_dcel.hpp"
#include "geo_sweepline_vertex.hpp"

namespace geo
{

class SweepLineState
{
public:
	DoubleEdgeList* dcel;
	double			reference_y;

	SweepLineState() = default;
	
	void initialize(
		const std::vector<Vector2>& points,
		std::priority_queue<SweepLineVertex *>& queue);

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