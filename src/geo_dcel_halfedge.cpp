#include "geo_dcel_halfedge.hpp"

namespace geo
{

DoubleEdgeListVertex* DoubleEdgeListHalfEdge::getDestination() const
{
	return this->next->origin;
}

DoubleEdgeListHalfEdge* DoubleEdgeListHalfEdge::getPrevious() const 
{
	DoubleEdgeListHalfEdge* edge = twin->next->twin;
	// walk around the face
	while (edge->next != this) {
		edge = edge->next->twin;
	}
	return edge;
}

DoubleEdgeListFace* DoubleEdgeListHalfEdge::getFace() const 
{
	return this->face;
}

}