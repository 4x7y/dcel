#ifndef GEO_DCEL_FACE_HPP
#define GEO_DCEL_FACE_HPP

namespace geo
{
class DoubleEdgeListHalfEdge;

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
