/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
//
// DARKROOM_SOURCE
//
#ifndef DARKROOM_SOURCE
#	error DARKROOM_SOURCE not defined. for example: "../../example/darkroom/two_spheres.hpp"
#else
#	include DARKROOM_SOURCE
#endif

//
// DARKROOM_TOTAL_WIDTH
// DARKROOM_TOTAL_HEIGHT
//
#ifndef DARKROOM_TOTAL_WIDTH
#	define DARKROOM_TOTAL_WIDTH 16
#endif
#ifndef DARKROOM_TOTAL_HEIGHT
#	define DARKROOM_TOTAL_HEIGHT DARKROOM_TOTAL_WIDTH
#endif

//
// DARKROOM_TILE_WIDTH
// DARKROOM_TILE_HEIGHT
//
#ifndef DARKROOM_TILE_WIDTH
#	define DARKROOM_TILE_WIDTH DARKROOM_TOTAL_WIDTH
#endif
#ifndef DARKROOM_TILE_HEIGHT
#	define DARKROOM_TILE_HEIGHT DARKROOM_TOTAL_HEIGHT
#endif

//
// DARKROOM_OFFSET_X
// DARKROOM_OFFSET_Y
//
#ifndef DARKROOM_OFFSET_X
#	define DARKROOM_OFFSET_X 0
#endif
#ifndef DARKROOM_OFFSET_Y
#	define DARKROOM_OFFSET_Y 0
#endif

#include <cstddef>
#include <iostream>
#include <sprout/darkroom.hpp>

namespace darkcult {
	SPROUT_STATIC_CONSTEXPR std::size_t total_width = DARKROOM_TOTAL_WIDTH;
	SPROUT_STATIC_CONSTEXPR std::size_t total_height = DARKROOM_TOTAL_HEIGHT;
	SPROUT_STATIC_CONSTEXPR std::size_t tile_width = DARKROOM_TILE_WIDTH;
	SPROUT_STATIC_CONSTEXPR std::size_t tile_height = DARKROOM_TILE_HEIGHT;
	SPROUT_STATIC_CONSTEXPR std::size_t offset_x = DARKROOM_OFFSET_X;
	SPROUT_STATIC_CONSTEXPR std::size_t offset_y = DARKROOM_OFFSET_Y;
}	// namespace darkcult

int main() {
	using namespace sprout::darkroom;

	typedef pixels::color_pixels<darkcult::tile_width, darkcult::tile_height>::type image_type;
	SPROUT_STATIC_CONSTEXPR auto image = pixels::generate<image_type>(
		darkcult::raytracer, darkcult::renderer, darkcult::camera,
		darkcult::object, darkcult::light,
		darkcult::offset_x, darkcult::offset_y,
		darkcult::total_width, darkcult::total_height
		);

	std::cout
		<< "P3" << std::endl
		<< image[0].size() << ' ' << image.size() << std::endl
		<< 255 << std::endl
		;
	for (auto i = image.begin(), last = image.end(); i != last; ++i) {
		auto const& line = *i;
		for (auto j = line.begin(), last = line.end(); j != last; ++j) {
			auto const& pixel = *j;
			std::cout
				<< unsigned(colors::r(pixel)) << ' '
				<< unsigned(colors::g(pixel)) << ' '
				<< unsigned(colors::b(pixel)) << std::endl
				;
		}
	}
}
