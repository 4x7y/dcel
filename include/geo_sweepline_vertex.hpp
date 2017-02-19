#ifndef GEO_SWEEPLINE_VERTEX_HPP
#define GEO_SWEEPLINE_VERTEX_HPP
#include "geo_vector2.hpp"
#include <iostream>

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

	bool isInteriorRight() const;

	bool isLeft(const SweepLineEdge* edge) const;

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
		std::cout << "y: " << this->ptr->point.y << " " << Vptr.ptr->point.y << std::endl;
		std::cout << "x: " << this->ptr->point.x << " " << Vptr.ptr->point.x << std::endl;

		if (*(this->ptr) < *(Vptr.ptr))
		{
			std::cout << " < \n\n";
			return true;
		}
		std::cout << " > \n\n";
		return false;
	}
};


} // namespace geo

#endif /* GEO_SWEEPLINE_VERTEX_HPP */