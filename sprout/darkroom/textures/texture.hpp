/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_TEXTURES_TEXTURE_HPP
#define SPROUT_DARKROOM_TEXTURES_TEXTURE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/array.hpp>
#include <sprout/darkroom/access/access.hpp>
#include <sprout/darkroom/colors/rgb.hpp>

//
// DARKROOM_LOAD_TEXTURE
//
#define DARKROOM_LOAD_TEXTURE <sprout/darkroom/load/texture.hpp>

//
// DARKROOM_TEX_VERSION
//
#define DARKROOM_TEX_VERSION(NUM) NUM

//
// DARKROOM_TEX_IMAGE_DEFAULT
//
#define DARKROOM_TEX_IMAGE_DEFAULT 0

//
// DARKROOM_TEX_PIXEL_INT_R8G8B8
//
#define DARKROOM_TEX_PIXEL_INT_R8G8B8 0

namespace sprout {
	namespace darkroom {
		namespace textures {
			//
			// version_type
			//
			typedef unsigned long version_type;
			//
			// info_type
			//
			struct info_type {
			public:
				unsigned long image_format;
				unsigned long pixel_format;
				std::size_t width;
				std::size_t height;
			};
			//
			// image_type
			//
			template<std::size_t Width, std::size_t Height, typename Color = sprout::darkroom::colors::rgb_f_t>
			struct image_type {
			public:
				typedef Color color_type;
				typedef color_type value_type;
				typedef std::size_t size_type;
				SPROUT_STATIC_CONSTEXPR size_type static_width = Width;
				SPROUT_STATIC_CONSTEXPR size_type static_height = Height;
				typedef sprout::array<value_type, static_width * static_height> pixels_type;
				typedef typename sprout::darkroom::access::unit<color_type>::type color_component_type;
			private:
				pixels_type pixels_;
			public:
				template<typename... Elems>
				SPROUT_CONSTEXPR image_type(info_type const&, Elems const&... elems)
					: pixels_{{
						color_type(
							static_cast<color_component_type>((elems >> 16) & 0xFF) / 0xFF,
							static_cast<color_component_type>((elems >> 8) & 0xFF) / 0xFF,
							static_cast<color_component_type>(elems & 0xFF) / 0xFF
							)...
						}}
				{
					static_assert(sizeof...(Elems) == static_width * static_height, "image_type<>: unmatch image size");
				}
				SPROUT_CONSTEXPR value_type const&
				operator()(size_type x, size_type y) const {
					return pixels_[y * static_width + x];
				}
				SPROUT_CONSTEXPR size_type
				width() const {
					return static_width;
				}
				SPROUT_CONSTEXPR size_type
				height() const {
					return static_height;
				}
				SPROUT_CONSTEXPR pixels_type const&
				pixels() const {
					return pixels_;
				}
			};
			template<std::size_t Width, std::size_t Height, typename Color>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::darkroom::textures::image_type<Width, Height, Color>::size_type
			sprout::darkroom::textures::image_type<Width, Height, Color>::static_width;
			template<std::size_t Width, std::size_t Height, typename Color>
			SPROUT_CONSTEXPR_OR_CONST typename sprout::darkroom::textures::image_type<Width, Height, Color>::size_type
			sprout::darkroom::textures::image_type<Width, Height, Color>::static_height;
		}	// namespace textures
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_TEXTURES_TEXTURE_HPP
