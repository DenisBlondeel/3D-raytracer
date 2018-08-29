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
			: x_P1(p1), x_P2(p2), x_P3(p3)
		{
			x_N = (x_P2 - x_P1).normalized().cross((x_P3 - x_P1).normalized());
		}
	private:
		Point3D x_P1;
		Point3D x_P2;
		Point3D x_P3;
		Vector3D x_N;

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override
		{
			double t = (x_P1 - ray.origin).dot(x_N) / (ray.direction.dot(x_N));
			Point3D hitPosition = ray.origin + ray.direction * t;
			std::vector<std::shared_ptr<Hit>> hits;
			Vector3D c1 = (x_P2 - x_P1).cross(hitPosition - x_P1);
			Vector3D c2 = (x_P3 - x_P2).cross(hitPosition - x_P2);
			Vector3D c3 = (x_P1 - x_P3).cross(hitPosition - x_P3);
			if (c1.dot(x_N) >= 0 && c2.dot(x_N) >= 0 && c3.dot(x_N) >= 0)
			{
				auto hit = std::make_shared<Hit>();
				hit->t = t;
				hit->position = ray.at(t);
				hit->local_position.xyz = hit->position;
				hit->local_position.uv = Point2D(0, 0);
				hits.push_back(hit);
			}
			return hits;
		}
		bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const override
		{
			auto t = this->find_all_hits(ray);
			if (t.size() != 0)
			{
				hit = t[0].get();
				return true;
			}
			else
			{
				return false;
			}
		}
		math::Box bounding_box() const override
		{
			// Create a [-1, 1] x [-1, 1] x [-1, 1] box.
			auto minX = std::min(std::min(x_P1.x(), x_P2.x()), x_P3.x());
			auto minY = std::min(std::min(x_P1.y(), x_P2.y()), x_P3.y());
			auto minZ = std::min(std::min(x_P1.z(), x_P2.z()), x_P3.z());

			auto maxX = std::max(std::max(x_P1.x(), x_P2.x()), x_P3.x());
			auto maxY = std::max(std::max(x_P1.y(), x_P2.y()), x_P3.y());
			auto maxZ = std::max(std::max(x_P1.z(), x_P2.z()), x_P3.z());

			return Box(interval(minX, maxX), interval(minY, maxY), interval(minZ, maxZ));
			//auto range = interval(-1.0, 1.0);

			//return Box(range, range, range);
		}
	};
}
Primitive raytracer::primitives::triangle(Point3D p1, Point3D p2, Point3D p3)
{
	return Primitive(std::make_shared<TriangleImplementation>(p1,p2,p3));
}