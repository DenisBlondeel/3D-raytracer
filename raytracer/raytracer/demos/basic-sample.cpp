#include "demos/basic-sample.h"
#include "demos/demo.h"
#include "util/lazy.h"
#include "easylogging++.h"

using namespace raytracer;
using namespace animation;
using namespace math;
using namespace imaging;
using namespace demos;


namespace
{
    class MeshDemo : public Demo
    {
    public:
        // C++ allows you to copy a superclass's constructor
        using Demo::Demo;

    protected:
		raytracer::RayTracer create_ray_tracer() override
		{
			return raytracers::v4();
		}

        /// <summary>
        /// Creates the root. This method will be called for several values of <paramref name="now" />,
        /// thus creating an animation.
        /// </summary>
        raytracer::Primitive create_root(TimeStamp now) override
        {
            // Local imports. Allows us to write sphere() instead of raytracer::primitives::sphere()
            using namespace raytracer::primitives;
            using namespace raytracer::materials;

            // Define material properties
            MaterialProperties material_properties(
                colors::blue() * 0.1,        // ambient lighting, not supported yet
                colors::blue() * 0.8,      // diffuse lighting, not supported yet
                colors::white() * 0.8,            // specular highlights, not supported yet
                0                           // specular exponent, not supported yet
            );
            // Create a uniform material: all parts of the primitive will be made out of the same material
            auto material = uniform(material_properties);
            // Create an animation of a double going from -5.0 to 5.0 in 1 second
            // It is important to write 5.0 and not 5, otherwise it will create an animation of ints instead of doubles
            auto x_position = animation::animate(-5.0, 5.0, 1_s);

			Point3D x(0, 0, 0);
			Point3D y(1, 0, 0);
			Point3D z(0, 1, 0);
            Primitive primitive = triangle(x,y,z);
            // Move the sphere. x_position(now) = asks the animation what x at this point in time
			// primitive = translate(Vector3D(x_position(now), 0, 0), primitive);

            // Assign a material to the sphere
            primitive = decorate(material, primitive);
            return primitive;
        }

        /// <summary>
        /// Creates light sources.
        /// </summary>
        std::vector<raytracer::LightSource> create_light_sources(TimeStamp now) override
        {
            // Local import
            using namespace raytracer::lights;

            std::vector<LightSource> light_sources;

			light_sources.push_back(lights::omnidirectional(Point3D(0, 5, 5), colors::white()));

            return light_sources;
        }

        /// <summary>
        /// Creates camera.
        /// </summary>
        raytracer::Camera create_camera(TimeStamp) override
        {
            return raytracer::cameras::perspective(
                Point3D(0, 0, 8),         // position of eye
                Point3D(0, 0, 0),          // point the camera looks at
                Vector3D(0, 1, 0),         // up-vector: indicates camera is "standing up"
                1,                         // distance between eye and viewing plane
                1                          // aspect ratio
            );
        }

    private:
        Primitive m_mesh;
    };
}

void demos::basic_sample(std::shared_ptr<pipeline::Consumer<std::shared_ptr<Bitmap>>> output)
{
    MeshDemo(500, 1_s, 1, 1).render(output);
}
