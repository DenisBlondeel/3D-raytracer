#include "cone-primitive.h"
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

	class ConeImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
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


			QuadraticEquation qeq(a, b, c);

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

	class ConeAlongZImplementation : public ConeImplementation
	{
	public:
		ConeAlongZImplementation()
			: ConeImplementation()
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
			return (ray.direction.x()*ray.direction.x()) + (ray.direction.y()*ray.direction.y()) - (ray.direction.z()*ray.direction.z());
			//return  Vector2D(ray.direction.x(), ray.direction.y()).dot(Vector2D(ray.direction.x(), ray.direction.y())) - (ray.direction.z()*ray.direction.z());
		}

		double calculateB(const Ray& ray) const {
			return (2 * ray.direction.x()*ray.origin.x()) + (2 * ray.direction.y()*ray.origin.y()) - (2 * ray.direction.z()*ray.origin.z());
			//return  2 * Vector2D(ray.direction.x(), ray.direction.y()).dot(Point2D(ray.origin.x(), ray.origin.y()) - Point2D(0, 0)) - 2 * (ray.direction.z()*ray.origin.z());
		}

		double calculateC(const Ray& ray) const {
			return (ray.origin.x()*ray.origin.x()) + (ray.origin.y()*ray.origin.y()) - (ray.origin.z()*ray.origin.z());
			//return  (Point2D(ray.origin.x(), ray.origin.y()) - Point2D(0, 0)).dot(Point2D(ray.origin.x(), ray.origin.y()) - Point2D(0, 0)) - (ray.origin.z()*ray.origin.z());
			
		}


	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			// Update Hit object
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
			
			Vector3D nor(hit->position.x(), hit->position.y(), 0);
			nor.normalize();
			hit->normal = nor;
			
			

		}
		

	};
	class ConeAlongYImplementation : public ConeImplementation
	{
	public:
		ConeAlongYImplementation()
			: ConeImplementation()
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
			return (ray.direction.x()*ray.direction.x()) + (ray.direction.z()*ray.direction.z()) - (ray.direction.y()*ray.direction.y());
			//return  Vector2D(ray.direction.x(), ray.direction.y()).dot(Vector2D(ray.direction.x(), ray.direction.y())) - (ray.direction.z()*ray.direction.z());
		}

		double calculateB(const Ray& ray) const {
			return (2 * ray.direction.x()*ray.origin.x()) + (2 * ray.direction.z()*ray.origin.z()) - (2 * ray.direction.y()*ray.origin.y());
			//return  2 * Vector2D(ray.direction.x(), ray.direction.y()).dot(Point2D(ray.origin.x(), ray.origin.y()) - Point2D(0, 0)) - 2 * (ray.direction.z()*ray.origin.z());
		}

		double calculateC(const Ray& ray) const {
			return (ray.origin.x()*ray.origin.x()) + (ray.origin.z()*ray.origin.z()) - (ray.origin.y()*ray.origin.y());
			//return  (Point2D(ray.origin.x(), ray.origin.y()) - Point2D(0, 0)).dot(Point2D(ray.origin.x(), ray.origin.y()) - Point2D(0, 0)) - (ray.origin.z()*ray.origin.z());

		}


	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			// Update Hit object
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.z());
			//hit->normal = Vector3D(hit->position.x() / hit->position.z(), hit->position.y() / hit->position.z(), 0);
			//Vector3D norm(hit->position.x() /t*hit->position.z(), hit->position.y() /t*hit->position.z(), 0);
			
			Vector3D nor(hit->position.x() , 0, hit->position.z() );
			nor.normalize();
			hit->normal = ray.direction.dot(nor) < 0 ? nor : -nor;



		}


	};
	class ConeAlongXImplementation : public ConeImplementation
	{
	public:
		ConeAlongXImplementation()
			: ConeImplementation()
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
			return (ray.direction.y()*ray.direction.y()) + (ray.direction.z()*ray.direction.z()) - (ray.direction.x()*ray.direction.x());
			//return  Vector2D(ray.direction.x(), ray.direction.y()).dot(Vector2D(ray.direction.x(), ray.direction.y())) - (ray.direction.z()*ray.direction.z());
		}

		double calculateB(const Ray& ray) const {
			return (2 * ray.direction.y()*ray.origin.y()) + (2 * ray.direction.z()*ray.origin.z()) - (2 * ray.direction.x()*ray.origin.x());
			//return  2 * Vector2D(ray.direction.x(), ray.direction.y()).dot(Point2D(ray.origin.x(), ray.origin.y()) - Point2D(0, 0)) - 2 * (ray.direction.z()*ray.origin.z());
		}

		double calculateC(const Ray& ray) const {
			return (ray.origin.y()*ray.origin.y()) + (ray.origin.z()*ray.origin.z()) - (ray.origin.x()*ray.origin.x());
			//return  (Point2D(ray.origin.x(), ray.origin.y()) - Point2D(0, 0)).dot(Point2D(ray.origin.x(), ray.origin.y()) - Point2D(0, 0)) - (ray.origin.z()*ray.origin.z());

		}


	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			// Update Hit object
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.y(), hit->position.z());
			
			//hit->normal = Vector3D(hit->position.x() / hit->position.z(), hit->position.y() / hit->position.z(), 0);
			//Vector3D norm(hit->position.x() /t*hit->position.z(), hit->position.y() /t*hit->position.z(), 0);
			double a = ray.origin.x();
			double b = t*ray.direction.x();
			double res = a * a + 2 * a*b + b*b;
			/*
			float r = sqrt((p.x - center.x)*(p.x - center.x) + (p.z - center.z)*(p.z - center.z));
			Vector n = Vector(p.x - center.x, r*(radius / height), p.z - center.z);
			n.normalise();
			return n;
			*/
			Vector3D nor(0, hit->position.y(), hit->position.z());
			nor.normalize();
			hit->normal = nor;


		}


	};
}

Primitive raytracer::primitives::cone_along_z()
{
	return Primitive(std::make_shared<ConeAlongZImplementation>());
}

Primitive raytracer::primitives::cone_along_y()
{
	return Primitive(std::make_shared<ConeAlongYImplementation>());
}


Primitive raytracer::primitives::cone_along_x()
{
	return Primitive(std::make_shared<ConeAlongXImplementation>());
}





