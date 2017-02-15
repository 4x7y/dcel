#ifndef GEO_SWEEPLINE_EDGE_HPP
#define GEO_SWEEPLINE_EDGE_HPP

namespace geo
{

class SweepLineEdge
{
	static double ref_y;

public:

	// Ax + By + C = 0;
	double A, B, C;

	double getX() const;

	bool operator< (const SweepLineEdge& edge) const;

	static void setReferenceY(double y);

};




} // namespace geo

#endif /* GEO_SWEEPLINE_EDGE_HPP */