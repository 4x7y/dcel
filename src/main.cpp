#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "geo_type.hpp"
#include "geo_dcel.hpp"
#include "geo_sweepline.hpp"
#include "geo_dcel_vertex.hpp"
#include "point_location.h"

#include <stdio.h>

using namespace std;
using namespace geo;

const uint WIN_WIDTH  = 512;
const uint WIN_HEIGHT = 512;

int main(int argc, const char * argv[])
{
	// Initialization
	cv::RNG rng;
	cv::Mat canvas(WIN_WIDTH, WIN_WIDTH, CV_8UC3);

	geo::DoubleEdgeList dcel;
	std::vector<geo::Vector2> points = {
		{400, 150}, {350, 350}, {300, 250}/*, {250, 300}, {300, 400},
		{200, 450}, {100, 350}, {200, 200}, {150, 150}, {250, 200},
		{300, 100} */};
	
	geo::SweepLine sweepline;
	std::vector<geo::Triangle> triangles;
	sweepline.triangulate(points, triangles,dcel);

    struct sort_x{
        bool operator()(const DoubleEdgeListVertex* v1,const DoubleEdgeListVertex* v2){
            return v1->point.x<v2->point.x;
        }
    };

    dcel.vertices.sort(sort_x());
    geo::PointLocation pl=PointLocation(&dcel);

    geo::Vector2 p;
    p.x=340;
    p.y=250;
    std::vector<double> v_list;
    geo::Triangle triangle;

    if(pl.Find_point_location(p,triangle))
        cout<<"Find it";
    else cout<<"Out of the polygon!"<<endl;


	for (auto triangle : triangles)
	{
		cv::Point triangle_vertices[1][3];
		triangle_vertices[0][0] = cv::Point(triangle.point1.x, triangle.point1.y);
		triangle_vertices[0][1] = cv::Point(triangle.point2.x, triangle.point2.y);
		triangle_vertices[0][2] = cv::Point(triangle.point3.x, triangle.point3.y);
		
		const cv::Point* ppt[1] = { triangle_vertices[0] };
		int npt[] = { 3 };

		cv::fillPoly(canvas, ppt, npt, 1,
		    cv::Scalar(rng.next() % 200 + 55, rng.next() % 200 + 55, rng.next() % 200 + 55),
			8);
	}


	// Visualization
	for (auto point : points)
	{
		circle(canvas, cv::Point2i(point.x, point.y), 1, cv::Scalar(200,100,200), 2);
	}
	imshow("Result", canvas);
	cv::waitKey();

	return 0;
}
