#pragma once
#include "raytracers/ray-tracer.h"
#include "raytracers/ray-tracer-v4.h"
#include "math/ray.h"
#include <memory>

namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV5 : public raytracer::raytracers::_private_::RayTracerV4
			{
				public:
					TraceResult trace(const Scene&, const math::Ray&) const override;
					virtual TraceResult trace(const Scene&, const math::Ray&,double ) const;
				protected:
					//imaging::Color process_light_ray(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, const LightRay&) const override;
					imaging::Color compute_reflection(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&,double) const;
			};
		}
		RayTracer v5();
	}
}