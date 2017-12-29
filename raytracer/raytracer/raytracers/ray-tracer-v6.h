#pragma once
#include "raytracers/ray-tracer.h"
#include "raytracers/ray-tracer-v5.h"
#include "math/ray.h"
#include <memory>

namespace raytracer
{
	namespace raytracers
	{
		namespace _private_
		{
			class RayTracerV6 : public raytracer::raytracers::_private_::RayTracerV5
			{
			public:
				TraceResult trace(const Scene&, const math::Ray&, double) const override;
			protected:
				imaging::Color compute_refraction(const Scene&, const MaterialProperties&, const Hit&, const math::Ray&, double) const;
			private:
			//	void compute_refracted_ray(double,double,Vector3D*) const;
			};
		}
		RayTracer v6();
	}
}
