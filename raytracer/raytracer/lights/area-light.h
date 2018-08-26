#pragma once

#include "lights\light-source.h"
#include "math\rectangle3d.h"
#include "samplers\sampler.h"
#include "imaging\color.h"
#include <memory>

namespace raytracer {
	namespace lights {
		LightSource area(const math::Rectangle3D& , const Sampler& , const imaging::Color& );
	}
}