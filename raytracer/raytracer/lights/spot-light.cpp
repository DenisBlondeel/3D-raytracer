#include "lights/spot-light.h"
using namespace math;
using namespace raytracer;
using namespace imaging;
namespace
{
	/// <summary>
	/// Implementation for omnidirectional point lights.
	/// </summary>
	class SpotLight: public raytracer::lights::_private_::PointLightImplementation
	{
	public:
			SpotLight(const math::Point3D& position, const math::Point3D& endPosition, const math::Angle& angle, const imaging::Color& color)
			: PointLightImplementation(position), m_color(color),m_endPosition(endPosition),m_angle(angle){ }

	protected:
		LightRay cast_lightray_to(const math::Point3D& p) const override
		{
			// Create ray starting at the light source's position and going through p
			math::Ray ray(m_position, m_endPosition);
			Vector3D v = ray.direction;
			Vector3D u = (p - m_position).normalized();
			if (u.dot(v) >= cos(m_angle / 2))
			{
				return LightRay(ray, m_color);
			}
			else
			{
				return LightRay(ray, colors::black());
			}
		}

	private:
		imaging::Color m_color;
		math::Point3D m_endPosition;
		Angle m_angle;
	};
}

LightSource raytracer::lights::spot(const math::Point3D& position,const math::Point3D& endPosition, const math::Angle& angle, const imaging::Color& color)
{
	return LightSource(std::make_shared<SpotLight>(position,endPosition,angle,color));
}