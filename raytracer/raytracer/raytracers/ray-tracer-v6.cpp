#include "raytracers/ray-tracer-v6.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

TraceResult raytracer::raytracers::_private_::RayTracerV6::trace(const Scene& scene, const math::Ray& ray, double weight) const
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
			result = result + compute_refraction(scene, properties, hit, ray, weight);
			return TraceResult(result, hit.group_id, ray, hit.t);
		}
		else
		{
			return TraceResult::no_hit(ray);
		}
	}
	return TraceResult::no_hit(ray);
}

imaging::Color raytracer::raytracers::_private_::RayTracerV6::compute_refraction(const Scene & scene, const MaterialProperties & mProp, const Hit & hit, const math::Ray & ray, double weight) const
{
	if (mProp.transparency > 0)
	{
		Vector3D n = hit.normal;
		Vector3D i = ray.direction.normalized();
		Vector3D ox = (1 / mProp.refractive_index) * (i - (i.dot(n) * n));
		auto ox2 = 1 - pow(ox.norm(), 2);
		if (ox2 < 0)
		{
			return colors::black();
		}
		Vector3D oy = -sqrt(ox2) * n;
		Vector3D o = ox + oy;
		Ray refrected_ray(hit.position + 0.00001 * o, o);
		Hit exit_hit;
		if (scene.root->find_first_positive_hit(refrected_ray, &exit_hit))
		{
			Vector3D ci = refrected_ray.direction.normalized();
			Vector3D cox = mProp.refractive_index / 1 * (ci - (ci.dot(exit_hit.normal) * exit_hit.normal));
			auto cox2 = 1 - pow(cox.norm(), 2);
			if (cox2 < 0)
			{
				return colors::black();
			}
			else
			{
				Vector3D coy = -sqrt(cox2) * n;
				Vector3D co = cox + coy;
				Ray exit_ray(exit_hit.position + 0.00001 * co, co);
				return raytracer::raytracers::_private_::RayTracerV6::trace(scene, exit_ray, weight * mProp.transparency).color;
			}
		}
		else
		{
			return colors::black();
		}
	}
	else
	{
		return colors::black();
	}
}
raytracer::RayTracer raytracer::raytracers::v6()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV6>());
}