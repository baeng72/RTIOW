#pragma once
#include "vec3.h"
#include "rtweekend.h"
//void write_color(unsigned* p, color pixel_color) {
//	int ir = static_cast<int>(255.999 * pixel_color.x());
//	int ig = static_cast<int>(255.999 * pixel_color.y());
//	int ib = static_cast<int>(255.999 * pixel_color.z());
//	*p = ib << 16 | ig << 8 | ir;
//}


//void write_color(unsigned* p, color pixel_color, int samples_per_pixel) {
//	auto r = pixel_color.x();
//	auto g = pixel_color.y();
//	auto b = pixel_color.z();
//
//	//Divide the color total by the number of samples.
//	auto scale = 1.0 / samples_per_pixel;
//
//	r *= scale;
//	g *= scale;
//	b *= scale;
//
//	int ir = static_cast<int>(256 * clamp(r, 0.0, 0.999));
//	int ig = static_cast<int>(256 * clamp(g, 0.0, 0.999));
//	int ib = static_cast<int>(256 * clamp(b, 0.0, 0.999));
//
//	*p = ib << 16 | ig << 8 | ir;
//
//}


void write_color(unsigned* p, color pixel_color, int samples_per_pixel) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();
	//Divide total color by number of samples and gamma-correct for gamma=2.0
	auto scale = 1.0 / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

		int ir = static_cast<int>(256 * clamp(r, 0.0, 0.999));
	int ig = static_cast<int>(256 * clamp(g, 0.0, 0.999));
	int ib = static_cast<int>(256 * clamp(b, 0.0, 0.999));

	*p = ib << 16 | ig << 8 | ir;


}