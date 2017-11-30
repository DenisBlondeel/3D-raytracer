#include "raytracers/ray-tracer-v4.h"
using namespace imaging;
using namespace math;
using namespace raytracer;

imaging::Color raytracer::raytracers::_private_::RayTracerV4::process_light_ray(const Scene& scene, const MaterialProperties& mProp, const Hit& hit, const math::Ray& ray, const LightRay& lightRay) const
{
	Hit lightHit;
	scene.root->find_first_positive_hit(lightRay.ray, &lightHit);
	if (lightHit.t > 1 || lightHit.t <= 0)
	{
		return colors::black();
	}
	else
	{
		return RayTracerV3::process_light_ray(scene, mProp, hit, ray, lightRay);
	}
}
raytracer::RayTracer raytracer::raytracers::v4()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV4>());
}