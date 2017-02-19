#include "geo_vector2.hpp"
#include "geo_sweepline.hpp"
#include "geo_sweepline_state.hpp"
#include "geo_sweepline_vertex.hpp"
#include "geo_sweepline_edge.hpp"
#include "geo_rbtree.hpp"
#include <queue>

using namespace geo;


GEO_RESULT SweepLine::triangulate(
	const std::vector<Vector2>& points,
	std::vector<Triangle>& triangles) const
{
	DoubleEdgeList dcel;
	createTriangulation(points, dcel);

	return GEO_RESULT::SUCCESS;
}

GEO_RESULT SweepLine::createTriangulation(const std::vector<Vector2>& points, DoubleEdgeList& dcel) const
{
	if (points.size() < 4)
	{
		return GEO_RESULT::INSUFFICIENT_POINTS;
	}

	double winding = getWinding(points);
	if (winding < 0)
	{
		// counter-clockwise
		return GEO_RESULT::FAILURE;
	}

	// Initialize a sweepline state controller
	SweepLineState* sweepstate = new SweepLineState();
	std::vector<SweepLineVertex *> sorted_vertex;

	std::priority_queue<SweepLineVertexPtr> queue;
	sweepstate->initialize(points, queue);

	while (!queue.empty())
	{
		SweepLineVertex* vertex = queue.top().ptr;
		queue.pop();

		switch (vertex->type)
		{
		case SweepLineVertexType::START:
			// Handle start vertex
			start(vertex, sweepstate);
			break;
		case SweepLineVertexType::END:
			end(vertex, sweepstate);
			// Handle end vertex
			break;
		case SweepLineVertexType::SPLIT:
			// Handle split vertex
			split(vertex, sweepstate);
			break;
		case SweepLineVertexType::MERGE:
			// Handle merge vertex
			merge(vertex, sweepstate);
			break;
		case SweepLineVertexType::REGULAR:
			// Handle regular vertex
			regular(vertex, sweepstate);
			break;

		default:
			// the program should not run here.
			return GEO_RESULT::FAILURE;
		}
	}

	// triangulate Y-Monotone Polygons in DCEL
	sweepstate->dcel->triangulateYMonotonePolygons();

	delete sweepstate;

	return GEO_RESULT::SUCCESS;
}

void SweepLine::start(SweepLineVertex* vertex, SweepLineState* sweepstate) const
{
	// we need to add the edge to the left to the tree
	// since the line in the next event may be intersecting it
	SweepLineEdge* leftEdge = vertex->left;
	// set the reference y to the current vertex's y
	sweepstate->reference_y = vertex->point.y;
	sweepstate->tree.insert(leftEdge);
	// set the left edge's helper to this vertex
	leftEdge->helper = vertex;
}

void SweepLine::end(SweepLineVertex* vertex, SweepLineState* sweepstate) const
{
	// if the vertex type is an end vertex then we
	// know that we need to remove the right edge
	// since the sweep line no longer intersects it
	SweepLineEdge* rightEdge = vertex->right;
	// before we remove the edge we need to make sure
	// that we don't forget to link up MERGE vertices
	if (rightEdge->helper->type == SweepLineVertexType::MERGE) {
		// connect v to v.right.helper
		sweepstate->dcel->addHalfEdges(vertex->index, rightEdge->helper->index);
	}
	// set the reference y to the current vertex's y
	sweepstate->reference_y = vertex->point.y;
	// remove v.right from T
	sweepstate->tree.delete_value(rightEdge);
}

void SweepLine::split(SweepLineVertex* vertex, SweepLineState* sweepstate) const
{
	// if we have a split vertex then we can find
	// the closest edge to the left side of the vertex
	// and attach its helper to this vertex
	SweepLineEdge* ej;
	sweepstate->tree.get_smaller(vertex, ej);

	// connect v to ej.helper
	sweepstate->dcel->addHalfEdges(vertex->index, ej->helper->index);

	// set the new helper for the edge
	ej->helper = vertex;
	// set the reference y to the current vertex's y
	sweepstate->reference_y = vertex->point.y;
	// insert the edge to the left of this vertex
	sweepstate->tree.insert(vertex->left);
	// set the left edge's helper
	vertex->left->helper = vertex;
}

void SweepLine::merge(SweepLineVertex* vertex, SweepLineState* sweepstate) const
{
	// get the previous edge
	SweepLineEdge* eiPrev = vertex->right;
	// check if its helper is a merge vertex
	if (eiPrev->helper->type == SweepLineVertexType::MERGE) {
		// connect v to v.right.helper
		sweepstate->dcel->addHalfEdges(vertex->index, eiPrev->helper->index);
	}
	// set the reference y to the current vertex's y
	sweepstate->reference_y = vertex->point.y;
	// remove the previous edge since the sweep 
	// line no longer intersects with it
	sweepstate->tree.delete_value(eiPrev);
	// find the edge closest to the given vertex
	SweepLineEdge* ej;
	sweepstate->tree.get_smaller(vertex, ej);

	// is the edge's helper a merge vertex
	if (ej->helper->type == SweepLineVertexType::MERGE) {
		// connect v to ej.helper
		sweepstate->dcel->addHalfEdges(vertex->index, ej->helper->index);
	}
	// set the closest edge's helper to this vertex
	ej->helper = vertex;
}

void SweepLine::regular(SweepLineVertex* vertex, SweepLineState* sweepstate) const
{
	// check if the interior is to the right of this vertex
	if (vertex->isInteriorRight())
	{
		// if so, check the previous edge's helper to see
		// if its a merge vertex
		if (vertex->right->helper->type == SweepLineVertexType::MERGE) {
			// connect v to v.right.helper
			sweepstate->dcel->addHalfEdges(vertex->index, vertex->right->helper->index);
		}
		// set the reference y to the current vertex's y
		sweepstate->reference_y = vertex->point.y;
		// remove the previous edge since the sweep 
		// line no longer intersects with it
		sweepstate->tree.delete_value(vertex->right);
		// add the next edge
		sweepstate->tree.insert(vertex->left);
		// set the helper
		vertex->left->helper = vertex;
	}
	else 
	{
		// otherwise find the closest edge
		SweepLineEdge* ej;
		sweepstate->tree.get_smaller(vertex, ej);
		// check the helper type
		if (ej->helper->type == SweepLineVertexType::MERGE) {
			// connect v to ej.helper
			sweepstate->dcel->addHalfEdges(vertex->index, ej->helper->index);
		}
		// set the new helper
		ej->helper = vertex;
	}
}

double SweepLine::getWinding(const std::vector<Vector2>& points) const
{
	// get the size
	int size = points.size();
	// the size must be larger than 1
	if (size < 2)
	{
		return 0;
	}

	// determine the winding by computing a signed "area"
	double area = 0.0;
	for (int i = 0; i < size; i++) {
		// get the current point and the next point
		Vector2 p1 = points[i];
		Vector2 p2 = points[i + 1 == size ? 0 : i + 1];
		// add the signed area
		area += p1.cross(p2);
	}
	// return the area
	return area;
}
