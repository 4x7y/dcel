#ifndef GEO_TYPE_HPP
#define GEO_TYPE_HPP

#include <list>

namespace geo
{

// 2 Dimension Point
template <typename _Tp> class Point2_
{
public:
	_Tp x, y;

	Point2_(_Tp x, _Tp y)
		: x(x)
		, y(y)
	{ }

	bool operator < (const Point2_ &p2);
};

template <typename _Tp>
bool Point2_<_Tp> :: operator < (const Point2_<_Tp> &p2)
{
	return (x < p2.x) || (x == p2.x && y < p2.y);
}

typedef Point2_<double> Point2d;
typedef Point2_<float>  Point2f;
typedef Point2_<int>    Point2i;

inline Point2i point2i(int x, int y)
{
	return Point2i(x, y);
}

inline Point2f point2f(float x, float y)
{
	return Point2f(x, y);
}

inline Point2d point2d(double x, double y)
{
	return Point2d(x, y);
}

// 3 Dimension Point
template <typename _Tp> class Point3_
{
public:
	_Tp x, y, z;

	Point3_(_Tp x, _Tp y, _Tp z)
		: x(x)
		, y(y)
		, z(z)
	{ }

	bool operator < (const Point3_ &p2);
};

template<typename _Tp>
bool Point3_<_Tp>::operator < (const Point3_<_Tp> &p2)
{
	return  (x < p2.x) ||
		(x == p2.x && y < p2.y) ||
		(x == p2.x && y == p2.y && z < p2.z);
}

typedef Point3_<double> Point3d;
typedef Point3_<float>  Point3f;
typedef Point3_<int>    Point3i;

inline Point3i point3i(int x, int y, int z)
{
	return Point3i(x, y, z);
}

inline Point3f point3f(float x, float y, float z)
{
	return Point3f(x, y, z);
}

inline Point3d point3d(double x, double y, double z)
{
	return Point3d(x, y, z);
}

// Edge
template <typename _Tp> class Edge2_
{
public:
	Point2_<_Tp> s, t;

	Edge2_(Point2_<_Tp> s, Point2_<_Tp> t)
		: s(s)
		, t(t)
	{ }
};

template <typename _Tp> class Edge3_ 
{
public:
	Point3_<_Tp> s, t;

	Edge3_(Point3_<_Tp> s, Point3_<_Tp> t)
		: s(s)
		, t(t)
	{ }
};

typedef Edge2_<double> Edge2d;
typedef Edge2_<float>  Edge2f;
typedef Edge2_<int>    Edge2i;

typedef Edge3_<double> Edge3d;
typedef Edge3_<float>  Edge3f;
typedef Edge3_<int>    Edge3i;

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
		Vertex* v1    = vpair.first;
		Vertex* v2    = vpair.second;

		edges.push_back(e12);
		edges.push_back(e21);

		e12->origin   = v1;
		e12->dst      = v2;
		e12->twin     = e21;
		v1->edgeFrom.push_back(e12);
		v2->edgeTo.push_back(e12);

		e21->origin   = v2;
		e21->dst      = v1;
		e21->twin     = e12;
		v2->edgeFrom.push_back(e21);
		v1->edgeTo.push_back(e21);

		return e12;
	}

	Face* addFace(const FaceDataT& data, const std::vector<HalfEdge *>& boundary)
	{
		Face* f = new Face(data);
		faces.push_back(f);

		size_t i;
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

		for	(auto f : faces)
		{
			delete f;
		}
	}
};

template <typename _Tp> class LineSegmentT
{
public:
	_Tp x_start;
	_Tp x_end;

	// Ax + By + C = 0
	_Tp A, B, C;

	LineSegmentT(_Tp x_start, _Tp x_end, _Tp A, _Tp B, _Tp C = 0)
		: x_start(x_start)
		, x_end(x_end)
		, A(A)
		, B(B)
		, C(C)
	{
		assert((x_end > x_start) && (0 != A || 0 != B));
	}

	bool isOverlap(_Tp x, _Tp y)
	{
		if (x < x_start || x > x_end)
		{
			return false;
		}

		_Tp value = A * x + B * y + C;
		
		return 0 == value ? true : false;
	}

	_Tp y(_Tp x)
	{
		if (0 == B)
		{
			return NAN;
		}

		return -(A * x + C) / B;
	}

	_Tp x(_Tp y)
	{
		if (0 == A)
		{
			return NAN;
		}

		return -(B * x + C) / A;
	}
};

} // namespace geo

#endif /* GEO_TYPE_HPP */
