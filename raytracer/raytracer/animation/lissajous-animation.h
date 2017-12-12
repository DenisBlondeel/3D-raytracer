#pragma once

#include "animation/animation.h"
#include "math/interval.h"


namespace animation
{
	template<typename T>
	Animation<T> lissajous(int x_amplitude, int y_amplitude, int x_frequency, int y_frequency, math::Angle x_phaseanimation::Duration duration)
	{
		
	}

	template<typename T>
	Animation<T> lissajous(int x_amplitude,int y_amplitude, int x_frequency, int y_frequency,math::Angle x_phase, animation::Duration duration)
	{
		return lissajous(x_amplitude, y_amplitude, x_frequency, y_frequency, x_phase, duration);
	}
}