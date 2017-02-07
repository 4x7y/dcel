#ifndef GEO_TRIANGULATION_HPP
#define GEO_TRIANGULATION_HPP

#include <queue>
#include "geo_type.hpp"
#include "geo_status.hpp"
#include "geo_dcel.hpp"

namespace geo
{

template <class VertexDataT, class EdgeDataT, class FaceDataT>
int PolygonTriangulation(DCEL<VertexDataT, EdgeDataT, FaceDataT> polygon)
{
	std::priority_queue<VertexT<VertexDataT, EdgeDataT, FaceDataT>> event_queue;
	Status<HalfEdgeT<VertexDataT, EdgeDataT, FaceDataT>> status;




	return 0;
}

} // namespace geo

#endif /* GEO_TRIANGULATION_HPP */
