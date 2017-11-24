#include <iostream>
#include <fstream>
#include "samplers/random-sampler.h"

using namespace math;
using namespace std;
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
			ofstream myfile;
			myfile.open("C:/Users/Denis/Desktop/console.txt");

			std::vector<Point2D> result;
			myfile << rectangle.center();
			myfile << rectangle.origin;
			myfile << rectangle.y_axis;
			myfile << rectangle.x_axis;
			for (int i = 0; i > m_sample_count; i++) 
			{

				
			}
				myfile.close();

			return result;
		}
	};
}

Sampler raytracer::samplers::random(int amount)
{
	return Sampler(std::make_shared<RandomSampler>(amount));
}