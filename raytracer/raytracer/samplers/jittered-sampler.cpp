#include <stdlib.h>
#include "samplers/stratified-sampler.h"
#include "math/rasterizer.h"

using namespace math;
using namespace raytracer;


namespace
{
	class Jittered : public raytracer::samplers::_private_::SamplerImplementation
	{


	public:
		Jittered(int N, int M) : N(N), M(M) {}
		int N;
		int M;

		std::vector<Point2D> sample(const math::Rectangle2D& rectangle) const override
		{
			std::vector<Point2D> result;
			Rasterizer rast(rectangle, N, M);

			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					Rectangle2D rect = rast[Position2D(N, M)];
					
					result.push_back(rect.from_relative(Point2D(rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.))));
				}
			}

			return result;
		}
	};
}

Sampler raytracer::samplers::stratified(int N, int M)
{
	return Sampler(std::make_shared<Jittered>(N, M));
}