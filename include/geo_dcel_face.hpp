#ifndef GEO_DCEL_FACE_HPP
#define GEO_DCEL_FACE_HPP

#include "geo_dcel_halfedge.hpp"

namespace geo
{

class DoubleEdgeListFace
{
public:

	DoubleEdgeListHalfEdge* edge;

	DoubleEdgeListFace()
		: edge(nullptr)
	{}

	int getEdgeCount() const;
};

} // namespace geo

#endif /* GEO_DCEL_FACE_HPP */
