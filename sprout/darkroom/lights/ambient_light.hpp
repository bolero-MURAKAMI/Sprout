/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_LIGHTS_AMBIENT_LIGHT_HPP
#define SPROUT_DARKROOM_LIGHTS_AMBIENT_LIGHT_HPP

#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/tuple/tuple.hpp>
#include <sprout/tuple/functions.hpp>
#include <sprout/darkroom/colors/rgb.hpp>
#include <sprout/darkroom/materials/material.hpp>
#include <sprout/darkroom/intersects/intersection.hpp>

namespace sprout {
	namespace darkroom {
		namespace lights {
			//
			// basic_ambient_light
			//
			template<typename Color = sprout::darkroom::colors::rgb_f_t>
			class basic_ambient_light {
			public:
				typedef Color color_type;
			private:
				color_type col_;
			public:
				explicit SPROUT_CONSTEXPR basic_ambient_light(color_type const& col)
					: col_(col)
				{}
				template<typename Intersection, typename Objects>
				SPROUT_CONSTEXPR color_type
				operator()(Intersection const& inter, Objects const&) const {
					return sprout::darkroom::colors::filter(
						col_,
						sprout::darkroom::materials::color(sprout::darkroom::intersects::material(inter))
						);
				}
			};
			//
			// make_ambient_light
			//
			template<typename Color>
			inline SPROUT_CONSTEXPR sprout::darkroom::lights::basic_ambient_light<Color>
			make_ambient_light(Color const& col) {
				return sprout::darkroom::lights::basic_ambient_light<Color>(col);
			}
		}	// namespace lights
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_LIGHTS_AMBIENT_LIGHT_HPP
