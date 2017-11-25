#include <stdlib.h>
#include "samplers/random-sampler.h"

using namespace math;
using namespace raytracer;


namespace
{
	class RandomSampler : public raytracer::samplers::_private_::SamplerImplementation
	{


	public:
		RandomSampler(int m_sample_count) :m_sample_count(m_sample_count) {}
		int m_sample_count;

		std::vector<Point2D> sample(const math::Rectangle2D& rectangle) const override
		{

			std::vector<Point2D> result;
				//result.push_back(rectangle.from_relative(Point2D(0.002, 0.5)));
				//result.push_back(rectangle.from_relative(Point2D(0.8, 0.6)));
				//result.push_back(rectangle.from_relative(Point2D(0.4, 0.2)));
			for (int i = 0; i < m_sample_count; i++) 
			{
			result.push_back(rectangle.from_relative(Point2D(rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.))));
			}

			return result;
		}
	};
}

Sampler raytracer::samplers::random(int amount)
{
	return Sampler(std::make_shared<RandomSampler>(amount));
}