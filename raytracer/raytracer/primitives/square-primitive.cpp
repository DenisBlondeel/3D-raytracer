#include "primitives/square-primitive.h"
#include "math/interval.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;


namespace
{
	/// <summary>
	/// Superclass for squares. Contains common logic.
	/// </summary>
	class CoordinateSquareImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	protected:
		const Vector3D m_normal;

		/// <summary>
		/// Constructor.
		/// </summary>
		/// <param name="normal">
		/// Normal vector on square. Needs to have unit length.
		/// </param>
		CoordinateSquareImplementation(const Vector3D& normal)
			: m_normal(normal)
		{
			assert(normal.is_unit());
		}

		virtual void initialize_hit(Hit* hit, const Ray& ray, double t) const = 0;

	public:
		std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
		{
			std::vector<std::shared_ptr<Hit>> hits;

			// Compute denominator
			double denom = ray.direction.dot(m_normal);

			// If denominator == 0, there is no intersection (ray runs parallel to plane)
			if (denom != approx(0.0))
			{
				// Compute numerator
				double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));

				// Compute t
				double t = numer / denom;

				// Create hit object
				auto hit = std::make_shared<Hit>();

				// shared_ptr<T>::get() returns the T* inside the shared pointer
				initialize_hit(hit.get(), ray, t);

				// Put hit in list
				Point2D local_position = hit->local_position.uv;
				if (abs(local_position[0]) <= 1 && abs(local_position[1]) <= 1)
				{
					hits.push_back(hit);
				}
			}

			return hits;
		}
	};

	class SquareXYImplementation : public CoordinateSquareImplementation
	{
	public:
		SquareXYImplementation()
			: CoordinateSquareImplementation(Vector3D(0, 0, 1))
		{
			// NOP
		}

		math::Box bounding_box() const override
		{
			return Box(interval(-1.0, 1.0), interval(-1.0, 1.0), interval(-0.01, 0.01));
		}

	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.y());
			hit->normal = ray.origin.z() > 0 ? m_normal : -m_normal;
		}

	};

	class SquareXZImplementation : public CoordinateSquareImplementation
	{
	public:
		SquareXZImplementation()
			: CoordinateSquareImplementation(Vector3D(0, 1, 0))
		{
			// NOP
		}

		math::Box bounding_box() const override
		{
			return Box(interval(-1.0, 1.0), interval(-0.01, 0.01), interval(-1.0, 1.0));
		}

	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.x(), hit->position.z());
			hit->normal = ray.origin.y() > 0 ? m_normal : -m_normal;
		}
	public:

		/*
		bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const override
		{
		double denom = ray.direction.dot(m_normal);

		// If denominator == 0, there is no intersection (ray runs parallel to plane)
		if (denom != approx(0.0))
		{
		// Compute numerator
		double numer = -((ray.origin - Point3D(0, 0, 0)).dot(m_normal));

		// Compute t
		double t = numer / denom;
		if (t > 0)
		{
		if (t < hit->t)
		{
		// Create hit object
		auto hit = std::make_shared<Hit>();

		// shared_ptr<T>::get() returns the T* inside the shared pointer
		initialize_hit(hit.get(), ray, t);
		return true;
		}
		else
		{
		return false;
		}
		}
		}
		*/
	};
	class SquareYZImplementation : public CoordinateSquareImplementation
	{
	public:
		SquareYZImplementation()
			: CoordinateSquareImplementation(Vector3D(1, 0, 0))
		{
			// NOP
		}

		math::Box bounding_box() const override
		{
			return Box(interval(-0.01, 0.01), interval(-1.0, 1.0), interval(-1.0, 1.0));
		}

	protected:
		void initialize_hit(Hit* hit, const Ray& ray, double t) const override
		{
			hit->t = t;
			hit->position = ray.at(hit->t);
			hit->local_position.xyz = hit->position;
			hit->local_position.uv = Point2D(hit->position.z(), hit->position.y());
			hit->normal = ray.origin.x() > 0 ? m_normal : -m_normal;
		}
	public:
		/*
		bool find_first_positive_hit(const math::Ray& ray, Hit* hit) const override
		{

		return true;
		}
		*/
	};
}

Primitive raytracer::primitives::xy_square()
{
	return Primitive(std::make_shared<SquareXYImplementation>());
}
Primitive raytracer::primitives::xz_square()
{
	return Primitive(std::make_shared<SquareXZImplementation>());
}
Primitive raytracer::primitives::yz_square()
{
	return Primitive(std::make_shared<SquareYZImplementation>());
}