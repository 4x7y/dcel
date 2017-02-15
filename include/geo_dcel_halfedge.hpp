#ifndef GEO_DCEL_HALFEDGE_HPP
#define GEO_DCEL_HALFEDGE_HPP

#include "geo_dcel_vertex.hpp"
#include "geo_dcel_face.hpp"

namespace geo
{

class DoubleEdgeListHalfEdge
{

public:

	DoubleEdgeListVertex	*origin;

	DoubleEdgeListHalfEdge	*twin;

	/* The incident half edge in the list having the same face */
	DoubleEdgeListHalfEdge	*next;

	/* The incident face of this half edge */
	DoubleEdgeListFace		*face;


	DoubleEdgeListHalfEdge()
		: origin(nullptr)
		, twin(nullptr)
		, next(nullptr)
		, face(nullptr)
	{}

	/* Return this half edge's destination. */
	DoubleEdgeListVertex* getDestination() const;

	/* Returns the previous half edge having the same face as this half edge. */
	DoubleEdgeListHalfEdge* getPrevious() const;

	/* Returns this half edge's face. */
	DoubleEdgeListFace* getFace() const;
};

} // namespace geo

#endif /* GEO_DCEL_HALFEDGE_HPP */