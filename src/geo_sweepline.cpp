#include "geo_sweepline.hpp"
#include "geo_dcel_halfedge.hpp"
#include "geo_sweepline_state.hpp"
#include <queue>


namespace geo
{
SweepLine::SweepLine()
{
}


SweepLine::~SweepLine()
{
}

GEO_RESULT SweepLine::createTriangulation(const std::vector<Vector2> points, DoubleEdgeList& dcel) const
{
	if (points.size() < 4)
	{
		return GEO_NOT_ENOUGH_POINT;
	}


	//// get the winding order
	// double winding = Geometry.getWinding(points);

	//// reverse the array if the points are in clockwise order
	//if (winding < 0.0) {
	//	Geometry.reverseWinding(points);
	//}

	//// create a new sweep state
	//// this is the container for the algorithms acceleration structures
	//SweepLineState* sweepstate = new SweepLineState();

	//// create the priority queue (sorted queue by largest y value) and
	//// the cyclical lists
	//std::priority_queue<SweepLineVertex> queue = sweepstate.initialize(points);

	//// Find all edges that need to be added to the polygon
	//// to create a y-monotone decomposition
	//while (!queue.isEmpty()) {
	//	SweepLineVertex vertex = queue.poll();
	//	if (vertex.type == SweepLineVertexType.START) {
	//		this.start(vertex, sweepstate);
	//	}
	//	else if (vertex.type == SweepLineVertexType.END) {
	//		this.end(vertex, sweepstate);
	//	}
	//	else if (vertex.type == SweepLineVertexType.SPLIT) {
	//		this.split(vertex, sweepstate);
	//	}
	//	else if (vertex.type == SweepLineVertexType.MERGE) {
	//		this.merge(vertex, sweepstate);
	//	}
	//	else if (vertex.type == SweepLineVertexType.REGULAR) {
	//		this.regular(vertex, sweepstate);
	//	}
	//}

	//// the DCEL now contains a valid y-monotone polygon decomposition
	//// next we need to triangulate all the y-monotone polygons
	//sweepstate.dcel.triangulateYMonotonePolygons();

	//// return the triangulation
	//return sweepstate.dcel;

	return GEO_SUCCESS;
}

}
