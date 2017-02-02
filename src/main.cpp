#include <iostream>
#include <opencv2/opencv.hpp>

#include "geo_type.hpp"
#include "geo_convex_hull.hpp"

#include <vector>
#include <queue>
#include <fstream>

const uint WIN_WIDTH  = 512;
const uint WIN_HEIGHT = 512;

class VertexData
{
public:
	geo::Point2i	pos;
	cv::Scalar		color;

	VertexData(int x, int y)
		: pos(x, y)
		, color(200, 20, 200)
	{}
};

class EdgeData
{
public:
	cv::Scalar		color;
	uint32_t		thickness;
	std::string		name;

	EdgeData(const std::string& name)
		: color(100, 50, 70)
		, thickness(1)
		, name(name)
	{}
};

class FaceData
{
public:
	cv::Scalar		color;
	uint32_t		area;

	FaceData() = default;
};

typedef geo::VertexT<VertexData, EdgeData, FaceData>	Vertex;
typedef geo::HalfEdgeT<VertexData, EdgeData, FaceData>	HalfEdge;
typedef geo::FaceT<VertexData, EdgeData, FaceData>		Face;
typedef geo::DCEL<VertexData, EdgeData, FaceData>		DCEL;

void generateDCEL(DCEL& dcel)
{
	std::vector<VertexData> vertex_datas = 
	{ {50, 50}, {50, 100}, {100, 100}, {100, 50}
	};

	std::vector<EdgeData> edge_datas = 
	{ {"12"}, {"23"}, {"34"}, {"41"}, {"13"}
	};

	std::vector<FaceData> face_datas(3);

	// Initialize vertices
	std::vector<Vertex *> vertex_ptrs;
	for (auto v : vertex_datas)
	{
		auto p = dcel.addVertex(v);
		vertex_ptrs.push_back(p);
	}

	// Initialize edges
	std::vector<HalfEdge *> halfedge_ptrs;
	halfedge_ptrs.push_back(dcel.addEdge(edge_datas[0], std::make_pair(vertex_ptrs[0], vertex_ptrs[1])));
	halfedge_ptrs.push_back(dcel.addEdge(edge_datas[1], std::make_pair(vertex_ptrs[1], vertex_ptrs[2])));
	halfedge_ptrs.push_back(dcel.addEdge(edge_datas[2], std::make_pair(vertex_ptrs[2], vertex_ptrs[3])));
	halfedge_ptrs.push_back(dcel.addEdge(edge_datas[3], std::make_pair(vertex_ptrs[3], vertex_ptrs[0])));
	halfedge_ptrs.push_back(dcel.addEdge(edge_datas[4], std::make_pair(vertex_ptrs[0], vertex_ptrs[2])));

	// Initialize faces
	std::vector<Face *> face_ptrs;
	std::vector<std::vector<HalfEdge *>> boundry = { 
		{ halfedge_ptrs[3]->twin,  halfedge_ptrs[2]->twin,  halfedge_ptrs[1]->twin,  halfedge_ptrs[0]->twin } ,
		{ halfedge_ptrs[0],  halfedge_ptrs[1],  halfedge_ptrs[4]->twin } ,
		{ halfedge_ptrs[4],  halfedge_ptrs[2],  halfedge_ptrs[3] } ,
	};
	for (size_t i = 0; i < face_datas.size(); i++)
	{
		dcel.addFace(face_datas[i], boundry[i]);
	}
}


void lineIntersect(const std::vector<geo::Edge2i>& seg, std::vector<geo::Point2i>& intersects)
{
	std::priority_queue<geo::Point2i> eventQueue;
	std::map<uint, geo::Edge2i>	status;
}

int main(int argc, const char * argv[])
{
	// DCEL Test
	auto dcel = new geo::DCEL<VertexData, EdgeData, FaceData>();
	generateDCEL(*dcel);
	delete dcel;

	// Initialization
	cv::RNG rng;
	cv::Mat canvas(WIN_WIDTH, WIN_WIDTH, CV_8UC3);
	std::vector<geo::Point2i> points;
	for (size_t i = 0; i < 10; i++)
	{
		points.push_back(
			geo::Point2i(rng.next() % WIN_WIDTH, rng.next() % WIN_HEIGHT));
	}
	
	// Test Function
	std::vector<geo::Edge2i> edges;
	convexHull(points, edges);
	
	// Visualization
	for (auto point : points)
	{
		circle(canvas, cv::Point2i(point.x, point.y), 1, cv::Scalar(200,100,200), 2);
	}
	imshow("Result", canvas);
	cv::waitKey();


	// Test line Intersection
	std::vector<geo::Edge2i> lineSeg;
	std::vector<geo::Point2i> intersects;

	geo::Edge2i e = geo::Edge2i(geo::Point2i(1,1), geo::Point2i(1, 1));

	return 0;
}
