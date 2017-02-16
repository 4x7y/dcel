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
	END,
	UNDEFINED
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
	int					index;

	SweepLineVertex(const Vector2& point, int i)
		: type(SweepLineVertexType::UNDEFINED)
		, prev(nullptr)
		, next(nullptr)
		, left(nullptr)
		, right(nullptr)
		, point(point)
		, index(i)
	{}

	bool isInteriorRight();

	// bool isLeft(const SweepLineEdge& edge);

	bool operator< (const SweepLineVertex& vertex) const;
};

class SweepLineVertexPtr
{
public:
	SweepLineVertex*	ptr;

	SweepLineVertexPtr(SweepLineVertex* ptr)
		: ptr(ptr) {}

	bool operator< (const SweepLineVertexPtr& Vptr) const
	{
		if (*(this->ptr) < *(Vptr.ptr))
		{
			return true;
		}
		return false;
	}
};


} // namespace geo

#endif /* GEO_SWEEPLINE_VERTEX_HPP */