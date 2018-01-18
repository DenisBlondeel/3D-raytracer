#pragma once

#include "imaging/bitmap.h"

namespace imaging
{
	void write_text_ppm(const Bitmap& bitmap, std::ostream& out);
}