#ifndef GEO_DCEL_VERTEX_HPP
#define GEO_DCEL_VERTEX_HPP

#include "geo_vector2.hpp"
#include "geo_dcel_halfedge.hpp"

namespace geo
{

class DoubleEdgeListVertex
{
public:

	/* The comparable data for this node */
	Vector2 point;

	/* The leaving edge */
	DoubleEdgeListHalfEdge* leaving;


	DoubleEdgeListVertex(const Vector2& point);

	DoubleEdgeListHalfEdge* getEdgeTo(DoubleEdgeListVertex* node) const;
};

}

#endif /* GEO_DCEL_VERTEX_HPP */