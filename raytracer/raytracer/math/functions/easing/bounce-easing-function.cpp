#include "math/functions/easing/bounce-easing-function.h"
#include "math/interval.h"
#include <assert.h>

using namespace math;
using namespace math::functions;


EasingFunction math::functions::easing::bounce(int number_of_bounces, int absorbation)
{
	std::function<double(double)> lambda = [](double t) {
		assert(interval(0.0, 1.0).contains(t));
		return t;
	};

	return from_lambda(lambda);
}