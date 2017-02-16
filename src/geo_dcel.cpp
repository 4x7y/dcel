#include "geo_dcel.hpp"
#include "geo_dcel_face.hpp"
#include "geo_dcel_halfedge.hpp"
#include "geo_dcel_vertex.hpp"

using namespace geo;

DoubleEdgeList::DoubleEdgeList(const std::vector<Vector2>& points)
{
	initialize(points);
}

DoubleEdgeList::~DoubleEdgeList()
{
	for (auto edge : edges)			delete edge;
	for (auto vertex : vertices)	delete vertex;
	for (auto face : faces)			delete face;
}

void DoubleEdgeList::initialize(const std::vector<Vector2>& points)
{
	int size = points.size();

	DoubleEdgeListFace* face = new DoubleEdgeListFace();
	faces.push_back(face);

	DoubleEdgeListHalfEdge* prevLeftEdge  = nullptr;
	DoubleEdgeListHalfEdge* prevRightEdge = nullptr;

	for (size_t i = 0; i < size; i++) 
	{
		auto point    = points[i];

		auto vertex   = new DoubleEdgeListVertex(point);
		auto left     = new DoubleEdgeListHalfEdge();
		auto right    = new DoubleEdgeListHalfEdge();

		left->face    = face;
		left->next    = nullptr;
		left->origin  = vertex;
		left->twin    = right;

		right->face   = nullptr;
		right->next   = prevRightEdge;
		right->origin = nullptr;
		right->twin   = left;

		edges.push_back(left);
		edges.push_back(right);

		vertex->leaving = left;
		vertices.push_back(vertex);

		if (prevLeftEdge != nullptr) {
			prevLeftEdge->next = left;
		}

		if (prevRightEdge != nullptr) {
			prevRightEdge->origin = vertex;
		}

		prevLeftEdge = left;
		prevRightEdge = right;
	}

	DoubleEdgeListHalfEdge* firstLeftEdge = edges.front();
	prevLeftEdge->next = firstLeftEdge;

	auto second = next(edges.begin(), 1);
	DoubleEdgeListHalfEdge* firstRightEdge = *second;
	firstRightEdge->next = prevRightEdge;

	prevRightEdge->origin = vertices.front();

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

void DoubleEdgeList::addHalfEdges(DoubleEdgeListVertex* v1, DoubleEdgeListVertex* v2)
{
	auto face = new DoubleEdgeListFace();

	auto left = new DoubleEdgeListHalfEdge();
	auto right = new DoubleEdgeListHalfEdge();

	auto referenceDoubleEdgeListFace = getReferenceFace(v1, v2);

	auto prev1 = getPreviousEdge(v1, referenceDoubleEdgeListFace);
	auto prev2 = getPreviousEdge(v2, referenceDoubleEdgeListFace);

	face->edge = left;
	referenceDoubleEdgeListFace->edge = right;

	left->face = face;
	left->next = prev2->next;
	left->origin = v1;
	left->twin = right;

	right->face = referenceDoubleEdgeListFace;
	right->next = prev1->next;
	right->origin = v2;
	right->twin = left;

	prev1->next = left;
	prev2->next = right;

	auto curr = left->next;
	while (curr != left) {
		curr->face = face;
		curr = curr->next;
	}

	edges.push_back(left);
	edges.push_back(right);

	faces.push_back(face);
}

DoubleEdgeListHalfEdge* DoubleEdgeList::getPreviousEdge(
	DoubleEdgeListVertex* vertex,
	DoubleEdgeListFace*	  face)
{
	auto twin = vertex->leaving->twin;
	auto edge = vertex->leaving->twin->next->twin;

	while (edge != twin) 
	{
		if (edge->face == face)
		{
			return edge;
		}
		edge = edge->next->twin;
	}

	return edge;
}

DoubleEdgeListFace* DoubleEdgeList::getReferenceFace(
	DoubleEdgeListVertex* v1,
	DoubleEdgeListVertex* v2)
{
	if (v1->leaving->face == v2->leaving->face)
	{
		return v1->leaving->face;
	}
		
	auto e1 = v1->leaving->twin->next->twin;
	while (e1 != v1->leaving->twin)
	{
		auto e2 = v2->leaving->twin->next->twin;
		while (e2 != v2->leaving->twin)
		{
			if (e1->face == e2->face) 
			{
				return e1->face;
			}
			e2 = e2->next->twin;
		}
		e1 = e1->next->twin;
	}

	return v1->leaving->face;
}

void DoubleEdgeList::removeHalfEdges(int index)
{
	auto iter = next(edges.begin(), index);
	auto e = *iter;
	removeHalfEdges(e);
}

void DoubleEdgeList::removeHalfEdges(DoubleEdgeListHalfEdge* edge)
{
	DoubleEdgeListFace* face = edge->twin->face;

	auto ePrev = edge->getPrevious();
	auto tPrev = edge->twin->getPrevious();
	auto eNext = edge->next;
	auto tNext = edge->twin->next;

	ePrev->next = tNext;
	tPrev->next = eNext;

	face->edge  = eNext;

	auto te = eNext;
	while (te != tNext)
	{
		te->face = face;
		te = te->next;
	}

	faces.remove(edge->face);
	delete edge->face;

	auto twin = edge->twin;

	edges.remove(edge);
	edges.remove(twin);
	delete edge;
	delete twin;
}
