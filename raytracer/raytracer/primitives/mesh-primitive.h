#pragma once

#include "primitives/primitive.h"
#include "math\vector.h"
#include "math\box.h"
namespace raytracer
{
	namespace primitives
	{
		Primitive mesh(std::vector<Primitive>& boxes, math::Box& box);
		Primitive meshbox(std::vector<Primitive>& boxes, math::Box& box);
	}
}