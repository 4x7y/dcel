#ifndef GEO_VECTOR2_HPP
#define GEO_VECTOR2_HPP

#include <math.h>

namespace geo
{
	class Vector2
	{

	public:
		double x;
		double y;
	
		Vector2()
			: x(0)
			, y(0)
		{}

		Vector2(double x, double y)
			: x(x)
			, y(y)
		{}
	
		Vector2(const Vector2& vector)
			: x(vector.x)
			, y(vector.y)
		{}

		Vector2(double x1, double y1, double x2, double y2)
			: x(x2 - x1)
			, y(y2 - y1)
		{}
	
		Vector2(const Vector2& vector1, const Vector2& vector2)
			: x(vector2.x - vector1.x)
			, y(vector2.y - vector1.y)
		{}

		Vector2(double direction)
			: x(cos(direction))
			, y(sin(direction))
		{}

		static Vector2 create(double magnitude, double direction);
		
		double	distance(double x, double y) const;
		
		double	distance(const Vector2& vector) const;
		
		double	distanceSquared(double x, double y) const;
		
		double	distanceSquared(const Vector2& vector) const;

		// (a x b) x c
		static	Vector2 tripleProduct(const Vector2& a, const Vector2& b, const Vector2& c);

		void	set(double x, double y);
		
		void	set(Vector2 vector);

		Vector2 getXComponent() const;

		Vector2 getYComponnet() const;

		double	getMagnitude() const;

		double	getMagnitudeSquared() const;

		void	setMagnitude(double magnitude);

		double	getDirection() const;

		void	setDirection(double angle);

		void	add(double x, double y);

		void	add(const Vector2& vector);

		void	substract(double x, double y);

		void	substract(const Vector2& vector);

		bool	isZero() const;

		double  cross(double x, double y) const;

		double  cross(const Vector2& vector) const;

		Vector2 to(const Vector2& vector) const;

		bool	operator== (const Vector2& vector) const;

		Vector2 operator+ (const Vector2& vector) const;

		Vector2 operator- (const Vector2& vector) const;

		double	operator* (const Vector2& vector) const;

		Vector2 operator*(const double& scalar) const;

		friend Vector2 operator*(const double& scalar, const Vector2& vector);

	};

} // namespace geo

#endif /* GEO_VECTOR2_HPP */