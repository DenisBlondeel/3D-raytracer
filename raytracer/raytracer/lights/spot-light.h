#pragma once

#include "lights/light-source.h"
#include "imaging/color.h"
#include "math/point.h"


namespace raytracer
{
	namespace lights
	{
		namespace _private_
		{
			LightSource spot(const math::Point3D& position,const math::Point3D& endPosition, const math::Angle angle, const imaging::Color& color);
		}
	}
}
