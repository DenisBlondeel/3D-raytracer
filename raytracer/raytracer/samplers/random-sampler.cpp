#include "samplers/random-sampler.h"

using namespace math;
using namespace raytracer;


namespace
{
	class RandomSampler : public raytracer::samplers::_private_::SamplerImplementation
	{
	public:
		void sample(const math::Rectangle2D& rectangle, std::function<void(const math::Point2D&)> function) const override
		{
			
		}
	};
}

Sampler raytracer::samplers::random(int)
{
	return Sampler(std::make_shared<RandomSampler>());
}