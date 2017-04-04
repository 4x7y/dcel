#ifndef GEO_VISUALIZE_HPP
#define GEO_VISUALIZE_HPP

#include <opencv/cv.h>
#include "geo_dcel.hpp"

namespace geo
{

namespace Render
{

static void draw(CvMat* canvas, const DoubleEdgeList& dcel);

}

}

#endif /* GEO_VISUALIZE_HPP */
