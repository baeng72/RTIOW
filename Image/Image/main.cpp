#include <iostream>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;
//use stb library to create jpg image
int main() {
	const int image_width = 256;
	const int image_height = 256;
	try
	{
		unsigned* imageData = (unsigned*)malloc(image_width * image_height * sizeof(unsigned int));//rgb data
		for (int j = 0; j < image_height; ++j) {
			unsigned y = image_height - j - 1;
			for (int i = 0; i < image_width; ++i) {
			//for(int i = image_width-1;i>=0;--i){
				auto r = double(i) / (image_width - 1);
				auto g = double(j) / (image_height - 1);
				auto b = 0.25;

				int ir = static_cast<int>(255.999 * r);
				int ig = static_cast<int>(255.999 * g);
				int ib = static_cast<int>(255.999 * b);
				
				
				unsigned* p = imageData + y * image_width + i;
				//unsigned* p = imageData + j * image_width + i;
				*p = ib << 16 | ig << 8 | ir;
			}
		}
		//save data
		cout << "Saving file" << endl;
		stbi_write_jpg("image.jpg", image_width, image_height, 4, imageData, 100);
		cout << "Freeing mem" << endl;
		free(imageData);
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
	catch (...)
	{
		cerr << "An exception occurred." << endl;
	}
	cout << "Done" << endl;
}