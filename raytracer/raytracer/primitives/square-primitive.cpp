#include "primitives/square-primitive.h"

using namespace raytracer;
using namespace raytracer::primitives;
using namespace math;

namespace {

class SquareXYImplementation : public raytracer::primitives::_private_::PrimitiveImplementation
{

public:	

	std::vector<std::shared_ptr<Hit>> find_all_hits(const math::Ray& ray) const override
	{

	}

};
}

Primitive raytracer::primitives::xy_square()
{
	return Primitive(std::make_shared<SquareXYImplementation>());
}
