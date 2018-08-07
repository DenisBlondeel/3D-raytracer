#pragma once

#include "pipeline/processor.h"
#include "imaging/wif-format.h"

namespace raytracer
{
	namespace pipeline
	{
		std::shared_ptr<Consumer<std::shared_ptr<imaging::Bitmap>>> ppm();
	}
}