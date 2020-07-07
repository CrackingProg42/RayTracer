
#include "tinyRT.hpp"
#include <fstream>

void initSDL() {
	std::cout << "Starting render" << std::endl;
}

void quitSDL() {
    std::cout << "end render" << std::endl;
}

void render(Vector3 *pix, int s) {
	fstream myfile;
	std::cout << "iter " << s << std::endl;
	if (s % 10 == 0) {
		myfile.open("render.ppm", fstream::out);
		myfile << "P3\n" << W << " " << H << "\n255\n";
		for (int col = 0; col < W; col++) {
			for (int row = 0; row < H; row++) {
				int pixel_index = col*W + row;
				myfile << std::min((int)(pix[pixel_index].x / (s + 1)), 255) << " ";
				myfile << std::min((int)(pix[pixel_index].y / (s + 1)), 255) << " ";
				myfile << std::min((int)(pix[pixel_index].z / (s + 1)), 255) << std::endl;
			}
		}
	}
}