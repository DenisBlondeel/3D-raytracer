#include <stdlib.h>
#include "samplers/multijittered-sampler.h"
#include "math/rasterizer.h"

using namespace math;
using namespace raytracer;


namespace
{
	class Multijittered : public raytracer::samplers::_private_::SamplerImplementation
	{
	public:
		Multijittered(int N) : N(N) {}
		int N;
		

		std::vector<Point2D> sample(const math::Rectangle2D& rectangle)const override
		{
			std::vector<Position2D> legalpositions;
			int pointer = 0;
			std::vector<Point2D> result;
			Rasterizer rast(rectangle, N, N);

			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					Rasterizer fineRast(rast[Position2D(j, i)], N, N);
					Rectangle2D rect = fineRast[legalpositions[pointer]];
					pointer++;
					result.push_back(rect.from_relative(Point2D(rand() / (RAND_MAX + 1.), rand() / (RAND_MAX + 1.))));

				}
			}

			return result;
		}

		int pickPos(std::vector<int> illegalPositions) const
		{
			

			int kol;
			kol = rand() % 2 * N + 1;

			if (std::find(illegalPositions.begin(), illegalPositions.end(), kol) != illegalPositions.end())
			{
				pickPos(illegalPositions);
			}
			else
			{
				illegalPositions.push_back(kol);
				return kol;
			}
		}

		std::vector<Position2D> createLegalPositionPool(std::vector<Position2D> legalPositions)
		{
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					legalPositions.push_back(Position2D(i, j));
				}
			}
			std::random_shuffle(legalPositions.begin(), legalPositions.end());
			return legalPositions;
		}
	};
}
	
Sampler raytracer::samplers::multijittered(int N)
{
	return Sampler(std::make_shared<Multijittered>(N));
}

