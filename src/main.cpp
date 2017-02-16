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
	std::vector<geo::Vector2> points;
	for (size_t i = 0; i < 10; i++)
	{
		points.push_back(
			geo::Vector2(rng.next() % WIN_WIDTH, rng.next() % WIN_HEIGHT));
	}
	
	geo::SweepLine sweepline;
	std::vector<geo::Triangle> triangles;
	sweepline.triangulate(points, triangles);
	
	// Visualization
	for (auto point : points)
	{
		circle(canvas, cv::Point2i(point.x, point.y), 1, cv::Scalar(200,100,200), 2);
	}
	imshow("Result", canvas);
	cv::waitKey();

	return 0;
}
