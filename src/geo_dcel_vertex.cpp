#include "geo_dcel_vertex.hpp"
#include "geo_dcel_halfedge.hpp"

namespace geo
{

DoubleEdgeListVertex::DoubleEdgeListVertex(const Vector2& point)
{
	this->point = point;
	this->leaving = nullptr;
}

DoubleEdgeListHalfEdge* DoubleEdgeListVertex::getEdgeTo(DoubleEdgeListVertex* node) const
{
	if (leaving != nullptr) 
	{
		if (leaving->twin->origin == node)
		{
			return leaving;
		}
		else
		{
			DoubleEdgeListHalfEdge* edge = leaving->twin->next;
			while (edge != leaving) 
			{
				if (edge->twin->origin == node) {
					return edge;
				}
				else {
					edge = edge->twin->next;
				}
			}
		}
	}
	return nullptr;
}

} // namespace geo