#include "vec3.h"
#include "color.h"
#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

int main() {
	const int image_width = 256;
	const int image_height = 256;

	unsigned* imageData = (unsigned*)malloc(image_width * image_height * sizeof(unsigned int));//rgb data
	for (int j = 0; j < image_height; ++j) {
		unsigned y = image_height - j - 1;
		for (int i = 0; i < image_width; ++i) {
			color pixel_color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0.25);
			
			unsigned* p = imageData + y * image_width + i;
			write_color(p, pixel_color);
			//unsigned* p = imageData + j * image_width + i;
			//*p = ib << 16 | ig << 8 | ir;
		}
	}
	//save data
	
	stbi_write_jpg("image.jpg", image_width, image_height, 4, imageData, 100);
	
	free(imageData);
}