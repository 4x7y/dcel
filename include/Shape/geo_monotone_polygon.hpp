#ifndef GEO_MONOTONE_POLYGON_HPP
#define GEO_MONOTONE_POLYGON_HPP
#include <list>

using std::list;

namespace geo
{
enum class MonotonePolygonType
{
	Y_MONOTONE = 0,
	X_MONOTONE = 1
};

enum class MonotoneChainType
{
	// Indicates that the vertex is on the left chain of a y-monotone polygon
	LEFT = 0,
	// Indicates that the vertex is on the right chain of a y-monotone polygon
	RIGHT = 1,
	// Indicates that the vertex is on the top chain of a x-monotone polygon
	TOP = 2,
	// Indicates that the vertex is on the bottom chain of a x-monotone polygon
	BOTTOM = 3
};

class MonotoneVertex
{
public:
	MonotoneVertex*		prev;
	MonotoneVertex*		next;

	// The monotone chain type indicator
	MonotoneChainType	type;

	// Todo: the monotone vertex data type should be a template type
	int					data;

	bool isAdjacent(const MonotoneVertex* v) const
	{
		if (v == prev || v == next) {
			return true;
		}
		return false;
	}
};

class MonotonePolygon
{
public:
	MonotonePolygonType		type;
	list<MonotoneVertex* >	vertices;

	MonotonePolygon(MonotonePolygonType type, list<MonotoneVertex* > vertices)
		: type(type)
		, vertices(vertices)
	{}
};

}
#endif
