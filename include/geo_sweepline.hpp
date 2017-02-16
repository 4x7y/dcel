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

class SweepLineVertex;
class SweepLineState;

class SweepLine
{
public:
	GEO_RESULT triangulate(
		const std::vector<Vector2>& points,
		std::vector<Triangle>& triangles) const;
	GEO_RESULT createTriangulation(
		const std::vector<Vector2>& points, DoubleEdgeList& triangles) const;

private:
	void start	(SweepLineVertex* vertex, SweepLineState* sweepstate);
	void end		(SweepLineVertex* vertex, SweepLineState* sweepstate);
	void split	(SweepLineVertex* vertex, SweepLineState* sweepstate);
	void merge	(SweepLineVertex* vertex, SweepLineState* sweepstate);
	void regular	(SweepLineVertex* vertex, SweepLineState* sweepstate);
};
}
#endif /* GEO_SWEEPLINE_HPP */