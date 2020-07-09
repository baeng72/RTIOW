#include "rtweekend.h"
#include "color.h"
#include "camera.h"
#include "hittable_list.h"
#include "sphere.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


color ray_color(const ray& r, const hittable& world,int depth) {
	hit_record rec;
	//If we've exceeded the ray bounce limit, no more light is gathered.
	if (depth <= 0)
		return color(0, 0, 0);
	if (world.hit(r, 0, infinity, rec)) {
		point3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5 * ray_color(ray(rec.p, target - rec.p), world,depth-1);
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main() {
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 384;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	const int samples_per_pixel = 100;
	const int max_depth = 50;

	hittable_list world;

	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	camera cam;


	unsigned* imageData = (unsigned*)malloc(image_width * image_height * sizeof(unsigned int));//rgb data
	for (int j = 0; j < image_height; ++j) {
		unsigned y = image_height - j - 1;
		for (int i = 0; i < image_width; ++i) {
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world,max_depth);
			}
			unsigned* p = imageData + y * image_width + i;
			write_color(p, pixel_color, samples_per_pixel);
		}
	}
	stbi_write_jpg("image.jpg", image_width, image_height, 4, imageData, 100);

	free(imageData);

}