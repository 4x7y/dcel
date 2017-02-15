#ifndef GEO_SWEEPLINE_STATE_HPP
#define GEO_SWEEPLINE_STATE_HPP

#include "geo_dcel.hpp"
#include <queue>

namespace geo
{

class SweepLineState
{
public:
	DoubleEdgeList* dcel;

	SweepLineState()
	{
		
	}
	
	void initialize(const std::vector<Vector2>& points, std::priority_queue<Vector2>& queue);

};

}

#endif /* GEO_SWEEPLINE_STATE_HPP */