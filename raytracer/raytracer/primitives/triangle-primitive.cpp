/*
#include "primitives/triangle-primitive.h"
#include "util/misc.h"
#include "math/coordinate-systems.h"
#include "math/quadratic_equation.h"
#include "performance/performance.h"
#include <assert.h>

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace
{
	class TriangleImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	public:
		TriangleImplementation(Point3D p1, Point3D p2, Point3D p3)
		: x_P1(p1), x_P2(p2), x_P3(p3){
	
		}
	private:
		Point3D x_P1;
		Point3D x_P2;
		Point3D x_P3;

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
		{
			Vector3D n = (x_P2 - x_P1).normalized().dot((x_P3 - x_P1).normalized());
			
			double t = (x_P1 - ray.origin).dot(n) / ray.direction.dot(n);
			Point3D hitPosition = ray.origin + ray.direction * t;
			auto hit = std::make_shared<Hit>();
			hit->t = t;
			hit->position = ray.at(t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = compute_uv_from_xyz(hit->position);
			hit->normal = compute_normal_at(ray, hit->position);
			std::vector<std::shared_ptr<Hit>> hits;
			hits.push_back(hit);
			return hits;
		}
		bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const override
		{
			return true;
		}
	};
}
Primitive raytracer::primitives::triangle(Point3D p1, Point3D p2, Point3D p3)
{
	return Primitive(std::make_shared<TriangleImplementation>(p1,p2,p3));
}
*/