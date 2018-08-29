#include "primitives/mesh-primitive.h"
#include "primitives/bounding-box.h"
#include "easylogging++.h"
#include "json.hpp"
#include "math\vector.h"
#include <fstream>
using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;
using json = nlohmann::json;
using namespace std;

bool sort_vector(std::shared_ptr<Hit> hit1, std::shared_ptr<Hit> hit2) {
	return hit1->t < hit2->t;
}

namespace
{
	class MeshImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	public:
		vector<Primitive> boxes;
		Box main_box;
		

		MeshImplementation(vector<Primitive>& boxes, Box& box) : boxes(boxes), main_box(box)
		{
			
		}



		vector<shared_ptr<Hit>> find_all_hits(const Ray& ray) const override {
			std::vector<std::shared_ptr<Hit>> hits;
			
			if (main_box.is_hit_by(ray)) {
				
					for (auto b : boxes) {
						if (b->bounding_box().is_hit_by(ray)) {
							for (auto hit : b->find_all_hits(ray))
							{
								hits.push_back(hit);
							}
						}
						
					}
			}
			std::sort(hits.begin(), hits.end(), sort_vector);

			return hits;
		}
		Box bounding_box() const override
		{
			return main_box;
		}


	};

	class MeshBoxImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
	{
	public:
		vector<Primitive> triangles;
		Box box;


		MeshBoxImplementation(vector<Primitive>& triangles, Box& b) : triangles(triangles), box(b)
		{

		}
		vector<shared_ptr<Hit>> find_all_hits(const Ray& ray) const override {
			std::vector<std::shared_ptr<Hit>> hits;
			
			
				for (auto p : triangles) {
					Hit hit;
						if (p->find_first_positive_hit(ray, &hit)) {
						hits.push_back(make_shared<Hit>(hit));
					}
				}
			
			
			

			//std::sort (hits.begin(), hits.end());
			std::sort(hits.begin(), hits.end(), sort_vector);

			return hits;
		}
		Box bounding_box() const override
		{
			return box;
		}

	};

	
}

Primitive raytracer::primitives::mesh(vector<Primitive>& boxes, Box& box )
{
	return Primitive(make_shared<MeshImplementation>(boxes, box));
}
Primitive raytracer::primitives::meshbox(vector<Primitive>& boxes, Box& box)
{
	return Primitive(make_shared<MeshBoxImplementation>(boxes, box));
}