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
	UNDEFINED = 0,
	// Indicates that the vertex is on the left chain of a y-monotone polygon
	LEFT = 1,
	// Indicates that the vertex is on the right chain of a y-monotone polygon
	RIGHT = 2,
	// Indicates that the vertex is on the top chain of a x-monotone polygon
	TOP = 3,
	// Indicates that the vertex is on the bottom chain of a x-monotone polygon
	BOTTOM = 4
};

class MonotoneVertex
{
public:
	MonotoneVertex*			prev;
	MonotoneVertex*			next;

	// The monotone chain type indicator
	MonotoneChainType		chain_type;

	// Todo: the monotone vertex data type should be a template type
	DoubleEdgeListVertex*	data;

	MonotoneVertex(DoubleEdgeListVertex* data)
		: prev(nullptr)
		, next(nullptr)
		, chain_type(MonotoneChainType::UNDEFINED)
		, data(data)
	{}

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
	MonotonePolygonType				type;
	std::vector<MonotoneVertex *>	vertices;

	MonotonePolygon() = default;

	MonotonePolygon(MonotonePolygonType type, std::vector<MonotoneVertex* > vertices)
		: type(type)
		, vertices(vertices)
	{}
};

}
#endif
