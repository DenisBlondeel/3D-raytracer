#include "math/functions/easing/bounce-easing-function.h"
#include "math/interval.h"
#include <assert.h>

using namespace math;
using namespace math::functions;


EasingFunction math::functions::easing::bounce(int number_of_bounces, int absorbation)
{
	double pi = 3.1415926535897;
	std::function<double(double)> lambda = [&](double t) {
		assert(interval(0.0, 1.0).contains(t));
		return 1 - abs(cos((2 * number_of_bounces - 1) * pi / 2 * t)) / pow(t+1,absorbation);
	};

	return from_lambda(lambda);
}