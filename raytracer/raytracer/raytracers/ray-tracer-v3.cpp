#include "raytracers/ray-tracer-v3.h"

using namespace imaging;
using namespace math;
using namespace raytracer;

imaging::Color raytracer::raytracers::_private_::RayTracerV3::process_light_ray(const Scene& scene, const MaterialProperties& mProp, const Hit& hit, const math::Ray& ray, const LightRay& lightRay)const
{
	Color result = raytracer::raytracers::_private_::RayTracerV2::process_light_ray(scene, mProp, hit, ray, lightRay);
	result = result + compute_specular(mProp, hit, ray, lightRay);
	return result;
}
imaging::Color raytracer::raytracers::_private_::RayTracerV3::compute_specular(const MaterialProperties& mProp, const Hit& hit, const math::Ray& ray, const LightRay& lightRay) const
{
	Color result;
	Point3D l = lightRay.ray.origin;
	Color cL = lightRay.color;
	Color cP = mProp.specular;
	Point3D p = hit.position;
	Vector3D n = hit.normal;
	Vector3D i = (p - l).normalized();
	auto r = i - 2 * (i.dot(n)) * n;
	Point3D eye = ray.origin;
	Vector3D v = (eye - p).normalized();
	auto e = v.reflect_by(n);
	double cosa = v.dot(r);
	if (cosa > 0)
	{
		result = cL * cP * pow(cosa,3.2);
	}
	else 
	{
		result = colors::black();
	}
		return result;
}

raytracer::RayTracer raytracer::raytracers::v3()
{
	return raytracer::RayTracer(std::make_shared<raytracer::raytracers::_private_::RayTracerV3>());
}