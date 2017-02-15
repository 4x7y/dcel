#ifndef GEO_SWEEPLINE_HPP
#define GEO_SWEEPLINE_HPP

#include <vector>
#include <list>

#include "geo_type.hpp"
#include "geo_vector2.hpp"
#include "geo_dcel.hpp"
#include "Shape/geo_triangle.hpp"

namespace geo
{
class SweepLine
{
public:
	SweepLine();
	~SweepLine();

	GEO_RESULT createTriangulation(const std::vector<Vector2>& points, DoubleEdgeList& triangles) const;

};
}
#endif /* GEO_SWEEPLINE_HPP */