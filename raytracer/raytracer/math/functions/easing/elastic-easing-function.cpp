#include "math/functions/easing/elastic-easing-function.h"
#include "math/interval.h"
#include <assert.h>
#include <math.h>

using namespace math;
using namespace math::functions;


EasingFunction math::functions::easing::elastic(int number_of_waves, int decay)
{
	double pi = 3.1415926535897;
	std::function<double(double)> lambda = [=](double t) {
		assert(interval(0.0, 1.0).contains(t));

		return exp(-t * decay) * sin(-2 * pi *number_of_waves * t);
	};

	return from_lambda(lambda);
}
