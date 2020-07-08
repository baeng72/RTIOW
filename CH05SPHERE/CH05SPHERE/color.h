#pragma once
#include "vec3.h"

void write_color(unsigned* p, color pixel_color) {
	int ir = static_cast<int>(255.999 * pixel_color.x());
	int ig = static_cast<int>(255.999 * pixel_color.y());
	int ib = static_cast<int>(255.999 * pixel_color.z());
	*p = ib << 16 | ig << 8 | ir;
}