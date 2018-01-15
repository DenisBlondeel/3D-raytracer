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
				std::vector<Point2D> result;
				Rasterizer rast(rectangle, N, M);

				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						Rectangle2D rect = rast[Position2D(N, M)];

						Point2D point = centralizing(rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.));

						result.push_back(rect.from_relative(point));
					}
				}

				return result;
			}

			Point2D centralizing(double x, double y) const
			{
				int centralX = x * 0.5 + 0.25;
				int centralY = y * 0.5 + 0.25;


				return Point2D(centralX, centralY);
			}
	};
}

Sampler raytracer::samplers::halfjittered(int N, int M)
{
	return	Sampler(std::make_shared<HalfJittered>(N, M))
}