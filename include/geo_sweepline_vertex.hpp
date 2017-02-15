#ifndef GEO_SWEEPLINE_VERTEX_HPP
#define GEO_SWEEPLINE_VERTEX_HPP
#include "geo_vector2.hpp"

namespace geo
{
class SweepLineEdge;

enum class SweepLineVertexType
{
	REGULAR,
	SPLIT,
	MERGE,
	START,
	END
};

class SweepLineVertex
{
public:
	SweepLineVertexType type;
	SweepLineVertex*	prev;
	SweepLineVertex*	next;

	SweepLineEdge*		left;
	SweepLineEdge*		right;

	Vector2				point;

	SweepLineVertex(Vector2 point, int i);
};

} // namespace geo

#endif /* GEO_SWEEPLINE_VERTEX_HPP */