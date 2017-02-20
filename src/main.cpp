#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#include "geo_type.hpp"
#include "geo_dcel.hpp"
#include "geo_sweepline.hpp"


const uint WIN_WIDTH  = 512;
const uint WIN_HEIGHT = 512;

int main(int argc, const char * argv[])
{
	// Initialization
	cv::RNG rng;
	cv::Mat canvas(WIN_WIDTH, WIN_WIDTH, CV_8UC3);

	geo::DoubleEdgeList dcel;
	std::vector<geo::Vector2> points = {
		{400, 150}, {300, 250}, {350, 350}, {250, 300}, {300, 400},
		{200, 450}, {100, 350}, {200, 200}, {150, 150}, {250, 200},
		{300, 100} };
	
	geo::SweepLine sweepline;
	std::vector<geo::Triangle> triangles;
	sweepline.triangulate(points, triangles);
	
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
