#pragma once
#include "primitives/primitive.h"

namespace raytracer
{
	namespace primitives
	{
		class OptMeshReader
		{
		public:
			Primitive read_mesh(std::string path);
		
		};

	}
}
