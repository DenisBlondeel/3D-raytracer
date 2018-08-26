#include "lights\area-light.h"
using namespace raytracer;
using namespace math;
using namespace imaging;

namespace {
	class AreaLight : public raytracer::lights::_private_::LightSourceImplementation
	{
	public:
		AreaLight(const Rectangle3D& rectangle, const Sampler& sampler, const Color& color ): m_area(rectangle), m_sampler(sampler),m_color(color){}

		std::vector<LightRay> lightrays_to(const math::Point3D& point) const override {

			Rectangle2D r(Point2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));
			std::vector<Point2D> picked =  m_sampler->sample(r);
			std::vector<LightRay> rays = {};
			
			for (int i = 0; i < picked.size(); i++) {
				//Point3D p = m_area.project(picked.at(0));
				//if (Ray(p, point).at(1) == point) {
				
				LightRay lr(Ray(m_area.project(picked.at(i)), point - m_area.project(picked.at(i))), m_color);
				rays.push_back(lr);
				//}
				//else {
					
				//}
			}
			
			
			return rays;
			

		}
		


	private:
		Rectangle3D m_area;
		Sampler m_sampler;
		Color m_color;

	};
}

LightSource raytracer::lights::area(const Rectangle3D& rectangle, const Sampler& sampler, const Color& color)
{
	return LightSource(std::make_shared<AreaLight>(rectangle, sampler,color));
}