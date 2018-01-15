#include <stdlib.h>
#include "samplers\halfjittered-sampler.h"
#include "math\rasterizer.h"

using namespace math;
using namespace raytracer;

namespace
{
	class HalfJittered : public raytracer::samplers::_private_::SamplerImplementation
	{
		public:
			HalfJittered(int N, int M) : N(N), M(M) {}
			int N;
			int M;

			std::vector<Point2D> sample(const math::Rectangle2D& rectangle)	const override
			{

			}
	};
}

Sampler raytracer::samplers::halfjittered(int N, int M)
{
	return	Sampler(std::make_shared<HalfJittered>(N, M))
}