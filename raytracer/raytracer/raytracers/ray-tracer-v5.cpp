/*
#include "raytracers/ray-tracer-v5.h"
using namespace imaging;
using namespace math;
using namespace raytracer;
/*
TraceResult trace(const Scene& scene, const math::Ray& ray, const double weight)
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
			unsigned group_id = hit.group_id;

			// The t-value indicates where the ray/scene intersection took place.
			// You can use ray.at(t) to find the xyz-coordinates in space.
			//double t = hit.t;
			//HitPosition p;
			//p.xyz = ray.at(t);
			MaterialProperties properties = hit.material->at(hit.local_position);
			// Group all this data into a TraceResult object.
			result = result + RayTracer::compute_ambient(properties);
			result = result + RayTracerV3::process_lights(scene, properties, hit, ray);
			return TraceResult(result, group_id, ray, hit.t);
	}
}
imaging::Color process_light_ray(const Scene& scene, const MaterialProperties& mProp, const Hit& hit, const math::Ray& ray, const LightRay& lightRay)
{

}
raytracer::RayTracer raytracer::raytracers::v5()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV5>());
}
*/