#include <stdlib.h>
#include "samplers/nrooks-sampler.h"
#include "math/rasterizer.h"

using namespace math;
using namespace raytracer;


namespace
{
	class Nrooks : public raytracer::samplers::_private_::SamplerImplementation
	{
		public:
			Nrooks(int N) : N(N) {}
			int N;

		std::vector<Point2D> sample(const math::Rectangle2D& rectangle)const override
		{
			std::vector<Point2D> result;
			Rasterizer rast(rectangle, N, N);

			

			for (int i = 0; i < N; i++)
			{
				int kol = pickPos();

				Rectangle2D rect = rast[Position2D(N, kol)];

				result.push_back(rect.from_relative(Point2D(rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.))));
			}
			
			return result;
		}

		int pickPos() const
		{
			std::vector<int> illegalPositions;

			int kol;
			kol = rand() % N + 1;

			if (std::find(illegalPositions.begin(), illegalPositions.end(), kol) != illegalPositions.end())
			{
				pickPos();
			}
			else
			{
				illegalPositions.push_back(kol);
				return kol;
			}
		}
	};
}

Sampler raytracer::samplers::nrooks(int N)
{
	return Sampler(std::make_shared<Nrooks>(N));
}

