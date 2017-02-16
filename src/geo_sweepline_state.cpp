#include "geo_sweepline_state.hpp"
#include "geo_sweepline_vertex.hpp"
#include "geo_sweepline_edge.hpp"

#include <limits>

using namespace geo;


bool Compare::less(SweepLineVertex* vertex, SweepLineEdge * edge) const
{
	return true;
}
bool Compare::less(SweepLineEdge* edge, SweepLineVertex* vertex) const
{
	return true;
}
bool Compare::less(SweepLineEdge* e1, SweepLineEdge* e2) const
{
	return true;
}

void SweepLineState::initialize(
		const std::vector<Vector2>& points,
		std::priority_queue<SweepLineVertexPtr>& queue)
{
	this->dcel = new DoubleEdgeList(points);

	int size = points.size();

	SweepLineVertex*  rootVertex = nullptr;
	SweepLineVertex*  prevVertex = nullptr;

	SweepLineEdge*	  rootEdge   = nullptr;
	SweepLineEdge*	  prevEdge   = nullptr;

	// Build the vertices and edges
	for (size_t i = 0; i < size; i++)
	{
		Vector2 point = points[i];

		// Create the vertex for this point
		SweepLineVertex* vertex = new SweepLineVertex(point, i);
		vertex->type = SweepLineVertexType::REGULAR;
		vertex->prev = prevVertex;

		// set the previous vertex's next pointer
		if (prevVertex != nullptr)
		{
			prevVertex->next = vertex;
		}

		if (rootVertex == nullptr)
		{
			rootVertex = vertex;
		}

		// get the neighbouring points
		Vector2 point1 = points[i + 1 == size ? 0 : i + 1];
		Vector2 point0 = points[i == 0 ? size - 1 : i - 1];
		
		// set the previous vertex to this vertex
		vertex->type = getType(point0, point, point1);

		// set the previous vertex to this vertex
		prevVertex = vertex;

		SweepLineVertexPtr vertex_ptr(vertex);
		queue.push(vertex_ptr);

		// create the next edge
		SweepLineEdge* e = new SweepLineEdge(&reference_y);
		e->v0 = vertex;

		// compute the slope
		double my = point.y - point1.y;
		if (my == 0.0)
		{
			e->slope_inverse = std::numeric_limits<double>::infinity();
		}
		else
		{
			double mx = point.x - point1.x;
			e->slope_inverse = (mx / my);
		}

		// set the previous edge's end vertex and 
		// next edge pointers
		if (prevEdge != nullptr)
		{
			prevEdge->v1 = vertex;
		}

		// make sure we save the first edge so we
		// can wire up the last and first create a
		// cycle list.
		if (rootEdge == nullptr)
		{
			rootEdge = e;
		}

		// set the vertex's left and right edges
		vertex->left = e;
		vertex->right = prevEdge;

		// set the previous edge to this edge
		prevEdge = e;
	}

	prevEdge->v1 = rootEdge->v0;

	rootVertex->right = prevEdge;
	rootVertex->prev  = prevVertex;
	prevVertex->next  = rootVertex;
}

SweepLineVertexType SweepLineState::getType(
	const Vector2& point_left,
	const Vector2& point,
	const Vector2& point_right) const
{
	// create the edge vectors
	Vector2 v1 = point_left.to(point);
	Vector2 v2 = point.to(point_right);

	// Both v1 and v2 should not be 0 vector

	// get the angle between the two edges (we assume CCW winding)
	double cross = v1.cross(v2);

	bool pBelowP0 = isBelow(point, point_left);
	bool pBelowP1 = isBelow(point, point_right);

	// where is p relative to its neighbors?
	if (pBelowP0 && pBelowP1) {
		// then check if the 
		// if its below both of them then we need
		// to check the interior angle
		if (cross > 0.0) {
			// if the cross product is greater than zero
			// this indicates that the angle is < pi

			// this vertex is an end vertex
			return SweepLineVertexType::END;
		} else {
			// this indicates that the angle is pi or greater

			// this vertex is a merge vertex
			return SweepLineVertexType::MERGE;
		}
	} else if (!pBelowP0 && !pBelowP1) {
		// if its above both of them then we need
		// to check the interior angle
		if (cross > 0.0) {
			// if the cross product is greater than zero
			// this indicates that the angle is < pi

			// this vertex is a start vertex
			return SweepLineVertexType::START;
		} else {
			// this indicates that the angle is pi or greater

			// this vertex is a split vertex
			return SweepLineVertexType::SPLIT;
		}
	}

	return SweepLineVertexType::REGULAR;
}


bool SweepLineState::isBelow(
	const Vector2& point1, const Vector2& point2) const
{
	double diff = point1.y - point2.y;
	if (diff == 0.0) {
		if (point1.x > point2.x) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (diff < 0.0) {
			return true;
		}
		else {
			return false;
		}
	}
}