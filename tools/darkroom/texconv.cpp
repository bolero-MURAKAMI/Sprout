/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
/*
  requires: OpenCV (http://opencv.jp/)
*/
#include <iostream>
#include <iomanip>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sprout/workaround/std/cstddef.hpp>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr
			<< "#error missing parameter.\n"
			<< std::flush
			;
		return 0;
	}

	cv::Mat image(cv::imread(argv[1]));
	std::cout
		<< "#if defined(DARKROOM_LOADING_TEXTURE_VERSION)\n"
			"\n"
			"DARKROOM_TEX_VERSION(0)\n"
			"\n"
			"#elif defined(DARKROOM_LOADING_TEXTURE_INFO)\n"
			"\n"
			"DARKROOM_TEX_IMAGE_DEFAULT,\n"
			"DARKROOM_TEX_PIXEL_INT_R8G8B8,\n"
		<< image.cols << ",\n"
		<< image.rows << "\n"
		<< "\n"
			"#elif defined(DARKROOM_LOADING_TEXTURE_PIXEL)\n"
			"\n"
		;

	std::cout << std::hex;
	for (std::size_t y = 0, h = image.rows; y != h; ++y) {
		for (std::size_t x = 0, w = image.cols; x != w; ++x) {
			auto pixel = image.ptr(y) + x * 3;
			std::cout
				<< "0x"
				<< std::setfill('0') << std::setw(2) << unsigned(pixel[2])
				<< std::setfill('0') << std::setw(2) << unsigned(pixel[1])
				<< std::setfill('0') << std::setw(2) << unsigned(pixel[0])
				;
			if (!(y == h - 1 && x == w - 1)) {
				std::cout << ',';
				if (x != w - 1) {
					std::cout << ' ';
				}
			}
		}
		std::cout << '\n';
	}
	std::cout << std::dec;

	std::cout
		<< "\n"
			"#endif\n"
		<< std::flush
		;
}
