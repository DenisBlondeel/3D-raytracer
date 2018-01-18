#include "ppm-format.h"


namespace imaging
{
	struct RGBColor
	{
		uint8_t r, g, b;

		RGBColor(const Color& c)
		{
			Color clamped = c.clamped();

			r = uint8_t(clamped.r * 255);
			g = uint8_t(clamped.g * 255);
			b = uint8_t(clamped.b * 255);
		}
	};

	void write_text_ppm(const Bitmap& bitmap, std::ostream& out)
	{
		out << "P6"; out << "\n";
		out << bitmap.width(); out << " ";
		out << bitmap.height(); out << "\n";
		out << 255; out << "\n"; 

		for (int i = 0; i<bitmap.height(); i++)
			for (int j = 0; j<bitmap.width(); j++)
			{
				RGBColor c = RGBColor(bitmap[Position2D(i, j)]);

				out << c.r << " " << c.g << " " << c.b << " \n";
			}

	}

}