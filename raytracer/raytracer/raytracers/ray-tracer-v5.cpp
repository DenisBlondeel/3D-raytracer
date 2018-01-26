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
		if (scene.root->find_first_positive_hit(ray, &hit))
		{
			MaterialProperties properties = hit.material->at(hit.local_position);
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
		auto r = ray.direction.reflect_by(n);
		Ray x_ray(hit.position + 0.00001 * r, r);
		double ref = mProp.reflectivity;
		return ref * trace(scene, x_ray, weight * mProp.reflectivity).color;
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