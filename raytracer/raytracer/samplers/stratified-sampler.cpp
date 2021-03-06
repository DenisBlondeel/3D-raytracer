#include <stdlib.h>
 #include "samplers/stratified-sampler.h"
 #include "math/rasterizer.h"

using namespace math;
using namespace raytracer;


namespace
 {
	class Stratified : public raytracer::samplers::_private_::SamplerImplementation
		 {
		
			
			public:
				Stratified(int N, int M) : N(N), M(M) {}
				int N;
				int M;
				
					std::vector<Point2D> sample(const math::Rectangle2D& rectangle) const override
					 {
					std::vector<Point2D> result;
					Rasterizer rast(rectangle, N, M);
					
						for (int i = 0; i <= N; i++)
						 {
						for (int j = 0; j <= M; j++)
							 {
							Position2D pos(N, M);
							
								Rectangle2D rect = rast[pos];
							
								Point2D cent = rect.center();
							result.push_back(cent);
							}
						}
					
						return result;
					}
				};
	}

Sampler raytracer::samplers::stratified(int N, int M)
 {
	return Sampler(std::make_shared<Stratified>(N, M));
	}