#include "raytracers/ray-tracer-v5.h"
using namespace imaging;
using namespace math;
using namespace raytracer;

TraceResult raytracer::raytracers::_private_::RayTracerV5::trace(const Scene& scene, const math::Ray& ray) const
{
	return trace(scene, ray,1.0);
}
TraceResult raytracer::raytracers::_private_::RayTracerV5::trace(const Scene& scene, const math::Ray& ray, double weight) const
{
	imaging::Color result = colors::black();
	if (weight > 0.01)
	{
		Hit hit;
		Color result = colors::black();
		// Ask the scene for the first positive hit, i.e. the closest hit in front of the eye
		// If there's a hit, find_first_positive_hit returns true and updates the hit object with information about the hit
		if (scene.root->find_first_positive_hit(ray, &hit))
		{
			// There's been a hit
			// Fill in TraceResult object with information about the trace

			// The hit object contains the group id, just copy it (group ids are important for edge detection)

			// The t-value indicates where the ray/scene intersection took place.
			// You can use ray.at(t) to find the xyz-coordinates in space.
			//double t = hit.t;
			//HitPosition p;
			//p.xyz = ray.at(t);
			MaterialProperties properties = hit.material->at(hit.local_position);
			// Group all this data into a TraceResult object.
			result = result + compute_ambient(properties);
			result = result + process_lights(scene, properties, hit, ray);
			result = result + compute_reflection(scene, properties, hit, ray, weight);
			return TraceResult(result, hit.group_id, ray, hit.t);
		}
		else
		{
			return TraceResult::no_hit(ray);
		}
	}
	return TraceResult::no_hit(ray);
}
imaging::Color raytracer::raytracers::_private_::RayTracerV5::compute_reflection(const Scene& scene, const MaterialProperties& mProp, const Hit& hit, const math::Ray& ray,double weight) const
{
	if (interval(0.0, 0.99999).contains(mProp.reflectivity))
	{
		Vector3D n = hit.normal;
		//Vector3D i = (ray.origin - hit.position).normalized();
		//Vector3D i = (hit.normal - ray.origin).normalized();
		//Vector3D r = i - 2 * (i.dot(n)) * n;
		auto r = ray.direction.reflect_by(n);
		Ray x_ray(hit.position + 0.00001 * r, r);
		double ref = mProp.reflectivity;
		return ref * trace(scene, x_ray, weight * mProp.reflectivity).color;
		//return imaging::colors::black();
	}
	else
	{
		return imaging::colors::black();
	}
}
raytracer::RayTracer raytracer::raytracers::v5()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV5>());
}