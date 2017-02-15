#include "geo_vector2.hpp"
#include "geo_epsilon.hpp"

namespace geo
{

Vector2 Vector2::create(double magnitude, double direction)
{
	double x = magnitude * cos(direction);
	double y = magnitude * sin(direction);

	return Vector2(x, y);
}

double Vector2::distance(double x, double y) const
{
	double dx = this->x - x;
	double dy = this->y - y;

	return sqrt(dx * dx + dy * dy);
}

double Vector2::distance(const Vector2& vector) const
{
	double dx = this->x - vector.x;
	double dy = this->y - vector.y;

	return sqrt(dx * dx + dy * dy);
}

double Vector2::distanceSquared(double x, double y) const
{
	double dx = this->x - x;
	double dy = this->y - y;

	return (dx * dx + dy * dy);
}

double Vector2::distanceSquared(const Vector2& vector) const
{
	double dx = this->x - vector.x;
	double dy = this->y - vector.y;

	return (dx * dx + dy * dy);
}

Vector2 Vector2::tripleProduct(const Vector2& a, const Vector2& b, const Vector2& c)
{
	Vector2 r;
	
	// perform a.dot(c)
	double ac = a.x * c.x + a.y * c.y;
	// perform b.dot(c)
	double bc = b.x * c.x + b.y * c.y;
	// perform b * a.dot(c) - a * b.dot(c)
	r.x = b.x * ac - a.x * bc;
	r.y = b.y * ac - a.y * bc;

	return r;
}

void	Vector2::set(double x, double y)
{
	this->x = x;
	this->y = y;
}

void	Vector2::set(Vector2 vector)
{
	this->x = vector.x;
	this->y = vector.y;
}

Vector2 Vector2::getXComponent() const
{
	Vector2 r;
	r.x = this->x;
	r.y = 0;

	return r;
}

Vector2 Vector2::getYComponnet() const
{
	Vector2 r;
	r.x = 0;
	r.y = this->y;

	return r;
}

double	Vector2::getMagnitude() const
{
	return sqrt(this->x * this->x + this->y * this->y);
}

double	Vector2::getMagnitudeSquared() const
{
	return (this->x * this->x + this->y * this->y);
}

void	Vector2::setMagnitude(double magnitude)
{
	// is this vector a zero vector?
	if (this->isZero()) {
		return;
	}
	// get the magnitude
	double mag = sqrt(this->x * this->x + this->y * this->y);
	// normalize and multiply by the new magnitude
	mag = magnitude / mag;
	this->x *= mag;
	this->y *= mag;
}

double	Vector2::getDirection() const
{
	return atan2(this->y, this->x);
}

void	Vector2::setDirection(double angle)
{
	double mag = sqrt(this->x * this->x + this->y * this->y);
	this->x = mag * cos(angle);
	this->y = mag * sin(angle);
}

void	Vector2::add(double x, double y)
{
	this->x += x;
	this->x += y;
}

void	Vector2::add(const Vector2& vector)
{
	this->x += vector.x;
	this->x += vector.y;
}

void	Vector2::substract(double x, double y)
{
	this->x -= x;
	this->x -= y;
}

void	Vector2::substract(const Vector2& vector)
{
	this->x -= vector.x;
	this->x -= vector.y;
}

bool	Vector2::isZero() const
{
	if (x < Epsilon::E && y < Epsilon::E)
	{
		return true;
	}

	return false;
}

double  Vector2::cross(double x, double y) const
{
	return this->x * y - this->y * x;
}

double  Vector2::cross(const Vector2& vector) const
{
	return this->x * vector.y - this->y * vector.x;
}

Vector2 Vector2::to(const Vector2& vector) const
{
	return Vector2(vector.x - this->x, vector.y - this->y);
}

Vector2 Vector2::operator+ (const Vector2& vector) const
{
	Vector2 r;

	r.x = this->x + vector.x;
	r.y = this->y + vector.y;

	return r;
}

Vector2 Vector2::operator- (const Vector2& vector) const
{
	Vector2 r;

	r.x = this->x - vector.x;
	r.y = this->y - vector.y;

	return r;
}

double Vector2::operator* (const Vector2& vector) const
{
	double x = this->x * vector.x;
	double y = this->y * vector.y;

	return x + y;
}

Vector2 Vector2::operator* (const double& scalar) const
{
	Vector2 r;

	r.x = scalar * this->x;
	r.y = scalar * this->y;

	return r;
}

Vector2 operator* (const double& scalar, const Vector2& vector)
{
	Vector2 r;

	r.x = scalar * vector.x;
	r.y = scalar * vector.y;

	return r;
}

bool Vector2::operator== (const Vector2& vector) const
{
	if (this->x == vector.x && this->y == vector.y)
	{
		return true;
	}

	return false;
}

}