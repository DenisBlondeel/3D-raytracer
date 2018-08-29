#include "primitives\opt-mesh-reader.h"
#include "primitives\mesh-primitive.h"
#include "json.hpp"
#include "math\box.h"
#include "math/interval.h"
#include "primitives\triangle-primitive.h"
#include <fstream>
#include "easylogging++.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;
using json = nlohmann::json;
using namespace std;

raytracer::Primitive raytracer::primitives::OptMeshReader::read_mesh(std::string path) {
	std::ifstream i(path);
	json j;
	i >> j;
	int n_boxes = j.size();
	std::vector<Primitive> boxes;

	for (int i = 0; i < n_boxes; i++) {
		vector<Primitive> box_triangles;
		double min_x = j[i]["v1"]["x"];
		double max_x = j[i]["v2"]["x"];
		double min_y = j[i]["v1"]["y"];
		double max_y = j[i]["v2"]["y"];
		double min_z = j[i]["v1"]["z"];
		double max_z = j[i]["v2"]["z"];
		math::Box box(math::interval(min_x, max_x), math::interval(min_y, max_y), math::interval(min_z, max_z));
		for (int t = 0; t < j[i]["triangles"].size(); t++) {
			double xx = j[i]["triangles"][t]["v1"]["x"];
			double xy = j[i]["triangles"][t]["v1"]["y"];
			double xz = j[i]["triangles"][t]["v1"]["z"];
			double yx = j[i]["triangles"][t]["v2"]["x"];
			double yy = j[i]["triangles"][t]["v2"]["y"];
			double yz = j[i]["triangles"][t]["v2"]["z"];
			double zx = j[i]["triangles"][t]["v3"]["x"];
			double zy = j[i]["triangles"][t]["v3"]["y"];
			double zz = j[i]["triangles"][t]["v3"]["z"];
			
			box_triangles.push_back(triangle(Point3D(xx, xy, xz), Point3D(yx, yy, yz), Point3D(zx, zy, zz)));
		}
		boxes.push_back(primitives::meshbox(box_triangles, box));
		LOG(INFO) << "[!] Size is " << boxes.size();
	}
	double min_x = j[0]["v1"]["x"];
	double max_x = j[n_boxes - 1]["v2"]["x"];
	double min_y = j[0]["v1"]["y"];
	double max_y = j[n_boxes - 1]["v2"]["y"];
	double min_z = j[0]["v1"]["z"];
	double max_z = j[n_boxes - 1]["v2"]["z"];
	math::Box b(math::interval(min_x, max_x), math::interval(min_y, max_y), math::interval(min_z, max_z));
	LOG(INFO) << "[!] Size is " << b.center();
	return primitives::mesh(boxes, b);


}