#include "lights\directional-light.h"

using namespace math;
using namespace imaging;
using namespace raytracer;

namespace {
	class DirectionalLight : public raytracer::lights::_private_::LightSourceImplementation 
	{
	public:
		DirectionalLight(const math::Vector3D& direction, const imaging::Color& color) : m_direction(direction), m_color(color){}

		std::vector<LightRay> lightrays_to(const math::Point3D& point) const override {

			math::Vector3D v = m_direction * 100;
			
			math::Ray ray(point - v  , point );
			
			
			return std::vector<LightRay> { LightRay(ray, m_color)};
			
				
			
			
		}



	private:
		math::Vector3D m_direction;
		imaging::Color m_color;

	};
}

LightSource raytracer::lights::directional(const math::Vector3D& direction, const imaging::Color& color) 
{
	return LightSource(std::make_shared<DirectionalLight>(direction, color));
}