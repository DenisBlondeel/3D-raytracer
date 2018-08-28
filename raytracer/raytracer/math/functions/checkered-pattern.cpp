#include "math/functions/checkered-pattern.h"
#include "math/functions.h"
#include <cmath>

using namespace math;


Function<bool(const Point2D&)> math::functions::checkered2d()
{
	std::function<bool(const Point2D&)> function = [](const Point2D& p)
	{
		auto x = round(p.x());
		auto y = round(p.y());
		int sum = x + y;

		return (sum % 2) == 0;
	};

	return from_lambda<bool, const Point2D&>(function);
}


