#include "cameras/fisheye-camera.h"
#include "math/interval.h"
#include "math/interval-mapper.h"
#include "math/angle.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::cameras;
using namespace math;


raytracer::cameras::_private_::FisheyeCamera::FisheyeCamera(const math::Matrix4x4 transformation, const math::Angle& horizontal, const math::Angle& vertical)
	: DisplaceableCamera(transformation), m_horizontal(horizontal), m_vertical(vertical)
{
	// NOP
}

void raytracer::cameras::_private_::FisheyeCamera::enumerate_untransformed_rays(const Point2D& point, std::function<void(const math::Ray&)> callback) const
{
	assert(interval(0.0, 1.0).contains(point.x()));
	assert(interval(0.0, 1.0).contains(point.y()));
	Angle ang = m_horizontal / 2;
	
	Interval<Angle> hor(-ang - 90_degrees , -180_degrees + ang + 90_degrees);  
	Interval<Angle> ver(-m_vertical/2, m_vertical/2);

	IntervalMapper<double, Angle> hor_map(Interval<double>(0.0, 1.0), hor);
	IntervalMapper<double, Angle> ver_map(Interval<double>(0.0, 1.0), ver);

	

	callback(Ray(math::Point3D(0, 0, 0), Point3D::spherical(1,  hor_map[point.x()], ver_map[point.y()])));
}

Camera raytracer::cameras::fisheye(
	const math::Point3D& eye,
	const math::Point3D& look_at,
	const math::Vector3D& up,
	 math::Angle horizontal,
	 math::Angle vertical)
{
	assert(up.is_unit());

	Matrix4x4 transformation = _private_::create_transformation(eye, look_at, up);

	return Camera(std::make_shared<_private_::FisheyeCamera>(transformation, horizontal, vertical));
}