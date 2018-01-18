#include "pipeline/ppm-consumer.h"
#include "imaging/ppm-format.h"

using namespace raytracer::pipeline;
using namespace imaging;


class Ppm : public Consumer<std::shared_ptr<imaging::Bitmap>>
{
public:
	void consume(std::shared_ptr<imaging::Bitmap> bitmap) override
	{
		write_text_ppm(*bitmap, std::cout);
	}
};


namespace raytracer
{
	namespace pipeline
	{
		std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> ppm()
		{
			return std::make_shared<Ppm>();
		}
	}
}