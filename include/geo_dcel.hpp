#ifndef GEO_DCEL_HPP
#define GEO_DCEL_HPP

#include <list>
#include <vector>

#include "geo_vector2.hpp"

namespace geo
{
	template <class VertexDataT, class HalfEdgeDataT, class FaceDataT>
	class FaceT;

	template <class VertexDataT, class HalfEdgeDataT, class FaceDataT>
	class HalfEdgeT;

	template<class VertexDataT, class HalfEdgeDataT, class FaceDataT>
	class VertexT
	{
		typedef VertexT<VertexDataT, HalfEdgeDataT, FaceDataT> Vertex;
		typedef HalfEdgeT<VertexDataT, HalfEdgeDataT, FaceDataT> HalfEdge;

	public:
		std::list<HalfEdge*> edgeFrom;
		std::list<HalfEdge*> edgeTo;
		VertexDataT data;

		VertexT(VertexDataT data)
			: edgeFrom()
			, edgeTo()
			, data(data)
		{};
	};

	template <class VertexDataT, class HalfEdgeDataT, class FaceDataT>
	class HalfEdgeT
	{
		typedef VertexT<VertexDataT, HalfEdgeDataT, FaceDataT> Vertex;
		typedef HalfEdgeT<VertexDataT, HalfEdgeDataT, FaceDataT> HalfEdge;
		typedef FaceT<VertexDataT, HalfEdgeDataT, FaceDataT> Face;

	public:
		HalfEdge*	twin;
		HalfEdge*	next;
		HalfEdge*	prev;
		Vertex*		origin;
		Vertex*		dst;
		Face*		face;
		HalfEdgeDataT data;

		HalfEdgeT() = default;

		HalfEdgeT(const HalfEdgeDataT& data) :
			twin(nullptr),
			next(nullptr),
			prev(nullptr),
			origin(nullptr),
			face(nullptr),
			data(data)
		{}
	};

	template <class VertexDataT, class HalfEdgeDataT, class FaceDataT>
	class FaceT
	{
		typedef FaceT<VertexDataT, HalfEdgeDataT, FaceDataT> Face;
		typedef HalfEdgeT <VertexDataT, HalfEdgeDataT, FaceDataT> HalfEdge;
	public:
		std::list<HalfEdge*> boundary;
		FaceDataT data;


		FaceT(const FaceDataT& data)
			: boundary()
			, data(data)
		{};
	};

	template <class VertexDataT, class HalfEdgeDataT, class FaceDataT>
	class DCEL
	{
		typedef VertexT<VertexDataT, HalfEdgeDataT, FaceDataT> Vertex;
		typedef HalfEdgeT<VertexDataT, HalfEdgeDataT, FaceDataT> HalfEdge;
		typedef FaceT<VertexDataT, HalfEdgeDataT, FaceDataT> Face;

		typedef std::pair<Vertex *, Vertex *> VertexPair;

		std::list<Face *> faces;
		std::list<Vertex *> vertices;
		std::list<HalfEdge *> edges;

	public:

		DCEL() = default;

		Vertex* addVertex(const VertexDataT& data)
		{
			Vertex* v = new Vertex(data);
			vertices.push_back(v);

			return v;
		}

		HalfEdge* addEdge(const HalfEdgeDataT& data, const VertexPair& vpair)
		{
			HalfEdge* e12 = new HalfEdge(data);
			HalfEdge* e21 = new HalfEdge(data);
			Vertex* v1 = vpair.first;
			Vertex* v2 = vpair.second;

			edges.push_back(e12);
			edges.push_back(e21);

			e12->origin = v1;
			e12->dst = v2;
			e12->twin = e21;
			v1->edgeFrom.push_back(e12);
			v2->edgeTo.push_back(e12);

			e21->origin = v2;
			e21->dst = v1;
			e21->twin = e12;
			v2->edgeFrom.push_back(e21);
			v1->edgeTo.push_back(e21);

			return e12;
		}

		Face* addFace(const FaceDataT& data, const std::vector<HalfEdge *>& boundary)
		{
			Face* f = new Face(data);
			faces.push_back(f);

			int i;
			for (i = 0; i < boundary.size(); i++)
			{
				f->boundary.push_back(boundary[i]);
				boundary[i]->face = f;
				boundary[i]->next = boundary[i == boundary.size() - 1 ? 0 : i + 1];
				boundary[i]->prev = boundary[i == 0 ? boundary.size() - 1 : i - 1];
			}

			return f;
		}

		~DCEL()
		{
			for (auto v : vertices)
			{
				delete v;
			}

			for (auto e : edges)
			{
				delete e;
			}

			for (auto f : faces)
			{
				delete f;
			}
		}
	};
}

namespace geo
{
class DoubleEdgeListFace;
class DoubleEdgeListHalfEdge;
class DoubleEdgeListVertex;
class MonotonePolygon;

class DoubleEdgeList
{
public:
	std::list<DoubleEdgeListVertex *>	vertices;
	std::list<DoubleEdgeListHalfEdge *>	edges;
	std::list<DoubleEdgeListFace *>		faces;

	DoubleEdgeList() = default;
	DoubleEdgeList(const std::vector<Vector2>& points);
	~DoubleEdgeList();

	void initialize(const std::vector<Vector2>& points);
	void addHalfEdges(int i, int j);
	void addHalfEdges(DoubleEdgeListVertex* v1, DoubleEdgeListVertex* v2);
	void removeHalfEdges(int index);
	void removeHalfEdges(DoubleEdgeListHalfEdge* edge);
	void triangulateYMonotonePolygons();

	static DoubleEdgeListHalfEdge*	getPreviousEdge(DoubleEdgeListVertex* vertex, DoubleEdgeListFace* face);
	static DoubleEdgeListFace*		getReferenceFace(DoubleEdgeListVertex* v1, DoubleEdgeListVertex* v2);

private:
	void triangulateYMonotonePolygon(const MonotonePolygon& monotonePolygon);
	void getYMonotonePolygons(std::vector<MonotonePolygon>& monotonePolygons);
};

}

#endif /* GEO_DCEL_HPP */