#include "cylinder-primitive.h"
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
	
	class CylinderImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	 
		virtual void initialize_hit(Hit* hit, const Ray& ray, double t) const = 0;
		virtual double calculateA(const Ray& ray) const = 0;
		virtual double calculateB(const Ray& ray) const = 0;
		virtual double calculateC(const Ray& ray) const = 0;
	public:

		bool find_first_positive_hit(const Ray& ray, Hit* hit) const override
		{
			assert(hit != nullptr);

			double a = calculateA(ray);
			double b = calculateB(ray);
			double c = calculateC(ray);

			QuadraticEquation qeq(a, b, c);

			if (qeq.has_solutions())
			{
				double t1 = qeq.x1();
				double t2 = qeq.x2();
				double t;

				// Find smallest positive t-value 
				if (smallest_greater_than_zero(t1, t2, &t))
				{
					// Check that our new t is better than the pre-existing t
					if (t < hit->t)
					{
						initialize_hit(hit, ray, t);

						return true;
					}
				}
			}

			return false;
		}

		std::vector<std::shared_ptr<Hit>> find_all_hits(const Ray& ray) const override {
			
			
			
			
			double a = calculateA(ray);
			double b = calculateB(ray);
			double c = calculateC(ray);
			
			
			QuadraticEquation qeq (a, b, c);

			if (qeq.has_solutions()) {

				// Quadratic equation has solutions: there are two intersections
				double t1 = qeq.x1();
				double t2 = qeq.x2();

				// We want t1 &lt; t2, swap them if necessary
				sort(t1, t2);

				// Sanity check (only performed in debug builds)
				assert(t1 <= t2);

				// Allocate vector on stack
				std::vector<std::shared_ptr<Hit>> hits;

				// Allocate two Hit objects on heap and store address in shared pointers
				auto hit1 = std::make_shared<Hit>();
				auto hit2 = std::make_shared<Hit>();

				// Initialize both hits
				initialize_hit(hit1.get(), ray, t1);
				initialize_hit(hit2.get(), ray, t2);

				// Put hits in vector
				hits.push_back(hit1);
				hits.push_back(hit2);

				// Return hit list
				return hits;
			}
			else
			{
				// No intersections to be found
				return std::vector<std::shared_ptr<Hit>>();
			}


		}
		

		math::Box bounding_box() const override
		{
			// Create a [-1, 1] x [-1, 1] x [-1, 1] box.
			auto range = interval(-1.0, 1.0);

			return Box(range, range, range);
		}
	};

	class CylinderAlongZImplementation : public CylinderImplementation
	{
	public:
		CylinderAlongZImplementation()
			: CylinderImplementation()
		{
			// NOP
		
		}

		
		math::Box bounding_box() const override
		{
			// Create a [-1, 1] x [-1, 1] x [-1, 1] box.
			auto range = interval(-1.0, 1.0);

			return Box(range, range, range);
		}


		double calculateA(const Ray& ray) const {
			return  Vector2D(ray.direction.x(), ray.direction.y()).dot(Vector2D(ray.direction.x(), ray.direction.y()));
		}

		double calculateB(const Ray& ray) const {
			return  2 * Vector2D(ray.direction.x(), ray.direction.y()).dot(Point2D(ray.origin.x(), ray.origin.y()) - Point2D(0, 0));
		}

		double calculateC(const Ray& ray) const {
			return  (Point2D(ray.origin.x(), ray.origin.y()) - Point2D(0, 0)).dot(Point2D(ray.origin.x(), ray.origin.y()) - Point2D(0, 0)) - 1;
		}


	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			// Update Hit object
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
			hit->normal = Vector3D(hit->position.x(), hit->position.y(), 0);


		}
		
	};
	class CylinderAlongYImplementation : public CylinderImplementation
	{
	public:
		CylinderAlongYImplementation()
			: CylinderImplementation()
		{
			// NOP

		}


		math::Box bounding_box() const override
		{
			// Create a [-1, 1] x [-1, 1] x [-1, 1] box.
			auto range = interval(-1.0, 1.0);

			return Box(range, range, range);
		}


		double calculateA(const Ray& ray) const {
			return  Vector2D(ray.direction.x(), ray.direction.z()).dot(Vector2D(ray.direction.x(), ray.direction.z()));
		}

		double calculateB(const Ray& ray) const {
			return  2 * Vector2D(ray.direction.x(), ray.direction.z()).dot(Point2D(ray.origin.x(), ray.origin.z()) - Point2D(0, 0));
		}

		double calculateC(const Ray& ray) const {
			return  (Point2D(ray.origin.x(), ray.origin.z()) - Point2D(0, 0)).dot(Point2D(ray.origin.x(), ray.origin.z()) - Point2D(0, 0)) - 1;
		}


	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			// Update Hit object
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.z());
			hit->normal = Vector3D(hit->position.x(), 0, hit->position.z());


		}

	};

	class CylinderAlongXImplementation : public CylinderImplementation
	{
	public:
		CylinderAlongXImplementation()
			: CylinderImplementation()
		{
			// NOP

		}


		math::Box bounding_box() const override
		{
			// Create a [-1, 1] x [-1, 1] x [-1, 1] box.
			auto range = interval(-1.0, 1.0);

			return Box(range, range, range);
		}


		double calculateA(const Ray& ray) const {
			return  Vector2D(ray.direction.y(), ray.direction.z()).dot(Vector2D(ray.direction.y(), ray.direction.z()));
		}

		double calculateB(const Ray& ray) const {
			return  2 * Vector2D(ray.direction.y(), ray.direction.z()).dot(Point2D(ray.origin.y(), ray.origin.z()) - Point2D(0, 0));
		}

		double calculateC(const Ray& ray) const {
			return  (Point2D(ray.origin.y(), ray.origin.z()) - Point2D(0, 0)).dot(Point2D(ray.origin.y(), ray.origin.z()) - Point2D(0, 0)) - 1;
		}


	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			// Update Hit object
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.y(), hit->position.z());
			hit->normal = Vector3D(0, hit->position.y(), hit->position.z());


		}

	};
}

Primitive raytracer::primitives::cylinder_along_z()
{
	return Primitive(std::make_shared<CylinderAlongZImplementation>());
}

Primitive raytracer::primitives::cylinder_along_x()
{
	return Primitive(std::make_shared<CylinderAlongXImplementation>());
}


Primitive raytracer::primitives::cylinder_along_y()
{
	return Primitive(std::make_shared<CylinderAlongYImplementation>());
}



