#include "geo_epsilon.hpp"

namespace geo
{
namespace Epsilon
{

double compute()
{
	double e = 0.5;
	while (1.0 + e > 1.0) {
		e *= 0.5;
	}
	return e;
}

} // namespace Epsilon

} // namespace geo

