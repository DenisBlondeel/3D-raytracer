#pragma once
#include "raytracers/ray-tracer.h"
#include "raytracers/ray-tracer-v3.h"
#include "math/ray.h"
#include <memory>

namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV4 : public raytracer::raytracers::_private_::RayTracerV3
			{
			protected:
				virtual imaging::Color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const override;
			};
		}
		RayTracer v4();
	}
}