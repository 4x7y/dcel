#include "geo_dcel.hpp"
#include "geo_dcel_face.hpp"
#include "geo_dcel_halfedge.hpp"
#include "geo_dcel_vertex.hpp"

namespace geo
{

DoubleEdgeList::DoubleEdgeList(const std::vector<Vector2>& points)
{
	initialize(points);
}

DoubleEdgeList::~DoubleEdgeList()
{
	for (auto edge : edges) delete edge;
	for (auto vertex : vertices) delete vertex;
	for (auto face : faces) delete face;
}

void DoubleEdgeList::initialize(const std::vector<Vector2>& points)
{
	// get the number of points
	int size = points.size();

	// we will always have exactly one face at the beginning
	DoubleEdgeListFace* face = new DoubleEdgeListFace();
	faces.push_back(face);

	DoubleEdgeListHalfEdge* prevLeftEdge = nullptr;
	DoubleEdgeListHalfEdge* prevRightEdge = nullptr;

	// loop over the points creating the vertices and
	// half edges for the data structure
	for (size_t i = 0; i < size; i++) 
	{
		auto point    = points[i];

		auto vertex   = new DoubleEdgeListVertex(point);
		auto left     = new DoubleEdgeListHalfEdge();
		auto right    = new DoubleEdgeListHalfEdge();

		// create and populate the left
		// and right half edges
		left->face    = face;
		left->next    = nullptr;
		left->origin  = vertex;
		left->twin    = right;

		right->face   = nullptr;
		right->next   = prevRightEdge;
		right->origin = nullptr;
		right->twin   = left;

		// add the edges the edge list
		edges.push_back(left);
		edges.push_back(right);

		// populate the vertex
		vertex->leaving = left;

		// add the vertex to the vertices list
		vertices.push_back(vertex);

		// set the previous next edge to this left edge
		if (prevLeftEdge != nullptr) {
			prevLeftEdge->next = left;
		}

		// set the previous right edge origin to this vertex
		if (prevRightEdge != nullptr) {
			prevRightEdge->origin = vertex;
		}

		// set the new previous edges
		prevLeftEdge = left;
		prevRightEdge = right;
	}

	// set the last left edge's next pointer to the
	// first left edge we created
	DoubleEdgeListHalfEdge* firstLeftEdge = edges.front();
	prevLeftEdge->next = firstLeftEdge;

	// set the first right edge's next pointer
	// to the last right edge we created
	// (note that right edges are at odd indices)
	auto second = std::next(edges.begin(), 1);
	DoubleEdgeListHalfEdge* firstRightEdge = *second;
	firstRightEdge->next = prevRightEdge;

	// set the last right edge's origin to the first
	// vertex in the list
	prevRightEdge->origin = vertices.front();

	// set the edge of the only face to the first
	// left edge
	// (note that the interior of each face has CCW winding)
	face->edge = firstLeftEdge;
}

void DoubleEdgeList::addHalfEdges(int i, int j)
{
	auto iter_i = next(vertices.begin(), i);
	auto vertex1 = *iter_i;
	auto iter_j = next(vertices.begin(), j);
	auto vertex2 = *iter_j;
	
	addHalfEdges(vertex1, vertex2);
}

void DoubleEdgeList::addHalfEdges(DoubleEdgeListVertex* v1, DoubleEdgeListVertex* v2) {
	// adding an edge splits the current face into two faces
	// so we need to create a new face
	auto face = new DoubleEdgeListFace();

	// create the new half edges for the new edge
	auto left = new DoubleEdgeListHalfEdge();
	auto right = new DoubleEdgeListHalfEdge();

	// find the reference face for these two vertices
	// the reference face is the face on which both the given
	// vertices are on
	auto referenceDoubleEdgeListFace = getReferenceFace(v1, v2);

	// get the previous edges for these vertices that are on
	// the reference face
	auto prev1 = getPreviousEdge(v1, referenceDoubleEdgeListFace);
	auto prev2 = getPreviousEdge(v2, referenceDoubleEdgeListFace);

	face->edge = left;
	referenceDoubleEdgeListFace->edge = right;

	// setup both half edges
	left->face = face;
	left->next = prev2->next;
	left->origin = v1;
	left->twin = right;

	right->face = referenceDoubleEdgeListFace;
	right->next = prev1->next;
	right->origin = v2;
	right->twin = left;

	// set the previous edge's next pointers to the new half edges
	prev1->next = left;
	prev2->next = right;

	// set the new face for all the edges in the left list
	auto curr = left->next;
	while (curr != left) {
		curr->face = face;
		curr = curr->next;
	}

	// add the new edges to the list
	edges.push_back(left);
	edges.push_back(right);

	// add the new face to the list
	faces.push_back(face);
}

DoubleEdgeListHalfEdge* DoubleEdgeList::getPreviousEdge(DoubleEdgeListVertex* vertex, DoubleEdgeListFace* face)
{
	// find the vertex on the given face and return the
	// edge that points to it
	auto twin = vertex->leaving->twin;
	auto edge = vertex->leaving->twin->next->twin;
	// look at all the edges that have their
	// destination as this vertex
	while (edge != twin) {
		// we can't use the getPrevious method on the leaving
		// edge since this doesn't give us the right previous edge
		// in all cases.  The real criteria is to find the edge that
		// has this vertex as the destination and has the same face
		// as the given face
		if (edge->face == face) {
			return edge;
		}
		edge = edge->next->twin;
	}
	// if we get here then its the last edge
	return edge;
}

DoubleEdgeListFace* DoubleEdgeList::getReferenceFace(DoubleEdgeListVertex* v1, DoubleEdgeListVertex* v2)
{
	// find the face that both vertices are on

	// if the leaving edge faces are already the same then just return
	if (v1->leaving->face == v2->leaving->face)
	{
		return v1->leaving->face;
	}
		
	// loop over all the edges whose destination is the first vertex (constant time)
	auto e1 = v1->leaving->twin->next->twin;
	while (e1 != v1->leaving->twin)
	{
		// loop over all the edges whose destination is the second vertex (constant time)
		auto e2 = v2->leaving->twin->next->twin;
		while (e2 != v2->leaving->twin)
		{
			// if we find a common face, that must be the reference face
			if (e1->face == e2->face) 
			{
				return e1->face;
			}
			e2 = e2->next->twin;
		}
		e1 = e1->next->twin;
	}

	// if we don't find a common face then return v1.leaving.face
	return v1->leaving->face;
}

void DoubleEdgeList::removeHalfEdges(int index) {

	auto iter = next(edges.begin(), index);
	auto e = *iter;
	removeHalfEdges(e);
}


void DoubleEdgeList::removeHalfEdges(DoubleEdgeListHalfEdge* edge)
{
	// wire up the two end points to remove the edge
	DoubleEdgeListFace* face = edge->twin->face;

	// we only need to re-wire the internal edges
	auto ePrev = edge->getPrevious();
	auto tPrev = edge->twin->getPrevious();
	auto eNext = edge->next;
	auto tNext = edge->twin->next;

	ePrev->next = tNext;
	tPrev->next = eNext;

	face->edge  = eNext;

	// set the face
	auto te = eNext;
	while (te != tNext)
	{
		te->face = face;
		te = te->next;
	}

	// remove the unneeded face
	faces.remove(edge->face);
	delete edge->face;

	auto twin = edge->twin;
	// remove the edges
	edges.remove(edge); // the edge
	edges.remove(twin); // the edge's twin
	delete edge;
	delete twin;
}
}
