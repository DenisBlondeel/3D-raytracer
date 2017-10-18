#include "raytracers/ray-tracer-v2.h"

using namespace imaging;
using namespace math;
using namespace raytracer;


TraceResult raytracer::raytracers::_private_::RayTracerV2::trace(const Scene& scene, const math::Ray& ray) const
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
		double t = hit.t;
		HitPosition p;
		p.xyz = ray.at(t);
		MaterialProperties properties = hit.material->at(p);
		// Group all this data into a TraceResult object.
		Color result = colors::black();
		result = result + compute_ambient(properties);
		result = result + process_lights(scene, properties, hit, ray);
		return TraceResult(compute_ambient(properties), group_id, ray, t);
	}
	else
	{
		// The ray missed all objects in the scene
		// Return a TraceResult object representing "no hit found"
		// which is basically the same as returning black
		return TraceResult::no_hit(ray);
	}
}
imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_lights(const Scene& scene, const MaterialProperties& mProp, const Hit& hit, const math::Ray& ray) const
{
	Color result = colors::black();
	for (LightSource lightSource : scene.light_sources)
	{
		result = result + process_light_source(scene, mProp, hit, ray, lightSource);
	}
	return result;
}
imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_source(const Scene& scene, const MaterialProperties& mProp, const Hit& hit, const math::Ray& ray, LightSource lightSource)const
{
	Color result = colors::black();
	Point3D test = ray.at(hit.t);
	std::vector<LightRay> l = lightSource->lightrays_to(test);
	for(LightRay lightray : l)
	{
		result = result + process_light_ray(scene, mProp, hit, ray, lightray);
	}
	return result;
}
imaging::Color raytracer::raytracers::_private_::RayTracerV2::process_light_ray(const Scene& scene, const MaterialProperties& mProp, const Hit& hit, const math::Ray& ray, const LightRay& lightRay)const
{
	Color result = colors::black();
	result = result + compute_diffuse(mProp, hit, ray, lightRay);
	return result;
}
imaging::Color raytracer::raytracers::_private_::RayTracerV2::compute_diffuse(const MaterialProperties& mProp, const Hit& hit, const math::Ray& ray, const LightRay& lightRay) const
{
	
	Point3D l = lightRay.ray.origin;
	Color cL = lightRay.color;
	Color cS = compute_ambient(mProp);
	Point3D p = lightRay.ray.at(hit.t);
	Vector3D n = ray.direction;
	Vector3D v = p - l;
	v.normalize();
	// std::cout << v.dot(n) * cL * cS;
	auto result = v.dot(n) * cL * cS;

	return result;
}
raytracer::RayTracer raytracer::raytracers::v2()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV2>());
}