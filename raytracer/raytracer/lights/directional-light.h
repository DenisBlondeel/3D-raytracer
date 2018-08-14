#pragma once

#include "lights\light-source.h"
#include "math\vector.h" 
#include "imaging\color.h"
#include <memory>
//#include "lights\light-ray.h"

namespace raytracer {
	namespace lights {
		LightSource directional(const math::Vector3D&, const imaging::Color&);
	}
}