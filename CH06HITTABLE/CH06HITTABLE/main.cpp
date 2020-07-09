#include "rtweekend.h"

#include "hittable_list.h"

#include "sphere.h"

#include <iostream>
#include "color.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
color ray_color(const ray& r, const hittable& world) {
	hit_record rec;
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + color(1, 1, 1));
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 384;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;

	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);

	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	unsigned* imageData = (unsigned*)malloc(image_width * image_height * sizeof(unsigned int));//rgb data
	for (int j = 0; j < image_height; ++j) {
		unsigned y = image_height - j - 1;
		for (int i = 0; i < image_width; ++i) {
			auto u = double(i) / (image_width - 1);
			auto v = double(j) / (image_height - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color pixel_color = ray_color(r,world);
			unsigned* p = imageData + y * image_width + i;
			write_color(p, pixel_color);
		}
	}
	stbi_write_jpg("image.jpg", image_width, image_height, 4, imageData, 100);

	free(imageData);
}