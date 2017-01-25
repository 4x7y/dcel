#include <iostream>
#include <opencv2/opencv.hpp>

#include "util.hpp"
#include "convexHull.hpp"

const uint WIN_WIDTH  = 512;
const uint WIN_HEIGHT = 512;

int main(int argc, const char * argv[])
{
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
    geo::convexHull(points, edges);
    
    // Visualization
    for (auto point : points)
    {
        circle(canvas, cv::Point2i(point.x, point.y), 1, cv::Scalar(200,100,200), 2);
    }
    imshow("Result", canvas);
    cv::waitKey();
    
    return 0;
}
