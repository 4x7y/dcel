#ifndef GEO_TRIANGLE_HPP
#define GEO_TRIANGLE_HPP

#include <geo_vector2.hpp>
#include <Shape/geo_polygon.hpp>

namespace geo
{
	class Triangle : public Polygon
	{
		Vector2 point1;
		Vector2 point2;
		Vector2 point3;

	public:

		Triangle(const Vector2& point1, const Vector2& point2, const Vector2& point3)
			: point1(point1)
			, point2(point2)
			, point3(point3)
		{}
	};
}

#endif /* GEO_TRIANGLE_HPP */
