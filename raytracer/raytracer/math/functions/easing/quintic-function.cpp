#include "math/functions/easing/quintic-function.h"
#include "math/interval.h"
#include <assert.h>

using namespace math;
using namespace math::functions;


EasingFunction math::functions::easing::quintic_in()
{
	std::function<double(double)> lambda = [](double t) {
		assert(interval(0.0, 1.0).contains(t));

		return pow(t, 5);
	};

	return from_lambda(lambda);
}

EasingFunction math::functions::easing::quintic_out()
{
	std::function<double(double)> lambda = [](double t) {
		assert(interval(0.0, 1.0).contains(t));

		return 1 + (--t)*t*t*t*t;
	};

	return from_lambda(lambda);
}

EasingFunction math::functions::easing::quintic_inout()
{
	std::function<double(double)> lambda = [](double t) {
		assert(interval(0.0, 1.0).contains(t));

		if (t <= 0.5)
		{
			return 16 * pow(t,5);
		}
		else
		{
			return 1 + 16 * (--t)*pow(t,4);
		}
	};

	return from_lambda(lambda);
}
