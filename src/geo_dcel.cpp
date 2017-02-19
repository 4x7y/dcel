#include "geo_dcel.hpp"
#include "geo_dcel_face.hpp"
#include "geo_dcel_halfedge.hpp"
#include "geo_dcel_vertex.hpp"
#include "Shape/geo_monotone_polygon.hpp"

#include <vector>
#include "geo_epsilon.hpp"

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

	for (int i = 0; i < size; i++) 
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

void DoubleEdgeList::triangulateYMonotonePolygons()
{
	std::vector<MonotonePolygon> monotonePolygons;
	
	getYMonotonePolygons(monotonePolygons);
	
	int size = monotonePolygons.size();
	for (int i = 0; i < size; i++) {
		triangulateYMonotonePolygon(monotonePolygons[i]);
	}
}

void DoubleEdgeList::getYMonotonePolygons(
	std::vector<MonotonePolygon>& monotonePolygons)
{
	// get the number of faces
	int fSize = faces.size();

	// create a list to store the y-monotone polygons
	monotonePolygons.reserve(fSize);

	// create a y-monotone polygon for each face
	for (auto face_iter = faces.begin(); face_iter != faces.end(); ++face_iter)
	{
		// get the face
		DoubleEdgeListFace* face = *face_iter;

		// Each face contains a y-monotone polygon.  We need to obtain a sorted
		// doubly-linked list of the vertices to triangulate easily.  We can create
		// the doubly-linked list while finding the maximum vertex in O(n) time.  
		// We can sort the list in O(n) time using the doubly-linked list we just
		// created.

		// get the number of Edges ( = the number of vertices) on this face
		int size = face->getEdgeCount();

		// get the reference edge of the face
		DoubleEdgeListHalfEdge* left = face->edge;

		// create the first vertex
		MonotoneVertex* root = new MonotoneVertex(left->origin);

		// move to the next origin
		left = left->next;

		// build the doubly linked list of vertices
		MonotoneVertex* prev = root;
		MonotoneVertex* curr = nullptr;
		MonotoneVertex* max = root;
		while (left != face->edge)
		{
			// create a new vertex
			curr = new MonotoneVertex(left->origin);
			curr->prev = prev;

			// set the previous vertex's next pointer to the new one
			prev->next = curr;

			// find the point with maximum y
			Vector2 p = curr->data->point;
			Vector2 q = max->data->point;
			// compare the y values
			double diff = p.y - q.y;
			if (diff == 0.0) {
				// if they are near zero then
				// compare the x values
				diff = p.x - q.x;
				if (diff < 0) {
					max = curr;
				}
			}
			else if (diff > 0.0) {
				max = curr;
			}

			// move to the next point
			left = left->next;

			// set the previous to the current
			prev = curr;
		}

		// wire up the last and first vertices
		root->prev = curr;
		curr->next = root;

		// create a sorted array of Vertices
		std::vector<MonotoneVertex *> sorted;
		sorted.reserve(size);

		// the first point is the vertex with maximum y
		sorted.push_back(max);
		// default the location to the left chain
		max->chain_type = MonotoneChainType::LEFT;

		// perform a O(n) sorting routine starting from the
		// maximum y vertex
		MonotoneVertex* currLeft  = max->next;
		MonotoneVertex* currRight = max->prev;
		//j starts at 1, skip the max vertex
		for (int j = 1; j < size; j++)
		{
			// get the left and right chain points
			Vector2 l = currLeft->data->point;
			Vector2 r = currRight->data->point;

			// which has the smaller y?
			if (l.y > r.y) {
				sorted.push_back(currLeft);
				currLeft->chain_type = MonotoneChainType::LEFT;
				currLeft = currLeft->next;
			}
			else {
				sorted.push_back(currRight);
				currRight->chain_type = MonotoneChainType::RIGHT;
				currRight = currRight->prev;
			}
		}
		// set the last point's chain to the right
		sorted[size - 1]->chain_type = MonotoneChainType::RIGHT;

		// add a new y-monotone polygon to the list
		monotonePolygons.push_back(
			MonotonePolygon(MonotonePolygonType::Y_MONOTONE, sorted));
	}
}

void DoubleEdgeList::triangulateYMonotonePolygon(
	const MonotonePolygon& monotonePolygon)
{
	// Todo: triangulate a single Y Monotone Polygon
	// create a stack to support triangulation
	std::vector<MonotoneVertex *> stack;

	// get the sorted monotone vertices
	std::vector<MonotoneVertex *> vertices = monotonePolygon.vertices;

	// a monotone polygon can be triangulated in O(n) time

	// push the first two onto the stack
	// push
	stack.push_back(vertices[0]);
	stack.push_back(vertices[1]);

	int i = 2;
	while (!stack.empty())
	{
		// get the next vertex in the sorted list
		MonotoneVertex* v = vertices[i];

		// get the bottom and top elements of the stack
		MonotoneVertex*  vBot = stack[0];
		MonotoneVertex*  vTop = stack[stack.size() - 1];

		// is the current vertex adjacent to the bottom element
		// but not to the top element?
		if (v->isAdjacent(vBot) && !v->isAdjacent(vTop))
		{
			// create the triangles and pop all the points
			while (stack.size() > 1) {
				// pop
				MonotoneVertex* vt = stack[stack.size() - 1];
				stack.resize(stack.size() - 1);
				// create diagonal
				addHalfEdges(v->data, vt->data);
			}
			// clear the bottom point
			stack.clear();

			// push the remaining edge
			stack.push_back(vTop);
			stack.push_back(v);
		}
		else if (v->isAdjacent(vTop) && !v->isAdjacent(vBot)) {
			double cross = 0;

			int sSize = stack.size();
			while (sSize > 1) {
				MonotoneVertex*  vt = stack[sSize - 1];
				MonotoneVertex*  vt1 = stack[sSize - 2];

				Vector2 p1 = v->data->point;
				Vector2 p2 = vt->data->point;
				Vector2 p3 = vt1->data->point;

				// what chain is the current vertex on
				if (v->chain_type == MonotoneChainType::LEFT ||
					v->chain_type == MonotoneChainType::BOTTOM)
				{
					Vector2 v1 = p2.to(p3);
					Vector2 v2 = p2.to(p1);
					cross = v1.cross(v2);
				}
				else {
					Vector2 v1 = p1.to(p2);
					Vector2 v2 = p3.to(p2);
					cross = v1.cross(v2);
				}

				// make sure the angle is less than pi before we create
				// a triangle from the points
				// epsilon is to handle near colinearity
				if (cross < Epsilon::E) {
					// add the half edges
					addHalfEdges(v->data, vt1->data);
					// remove the top element
					// pop
					stack.resize(sSize - 1);
					sSize--;
				}
				else {
					// once we find an angle that is greater than pi then
					// we can quit and move to the next vertex in the sorted list
					break;
				}
			}
			stack.push_back(v);
		}
		else if (v->isAdjacent(vTop) && v->isAdjacent(vBot)) {
			// create the triangles and pop all the points
			// pop
			stack.resize(stack.size() - 1);
			while (stack.size() > 1) {
				// pop
				MonotoneVertex* vt = stack[stack.size() - 1];
				stack.resize(stack.size() - 1);

				// create diagonal
				addHalfEdges(v->data, vt->data);
			}
			// we are done
			break;
		}
		i++;
	}

}