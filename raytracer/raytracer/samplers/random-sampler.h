#pragma once

#include "samplers/sampler.h"


namespace raytracer
{
	namespace samplers
	{
		/// <summary>
		/// Creates a sampler that picks random points winthin the given rectangle.
		/// </summary>
		Sampler random(int);
	}
}
#pragma once
