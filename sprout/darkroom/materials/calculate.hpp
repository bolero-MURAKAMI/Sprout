/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_MATERIALS_CALCULATE_HPP
#define SPROUT_DARKROOM_MATERIALS_CALCULATE_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace darkroom {
		namespace materials {
			//
			// calculate_result
			//
			template<typename Image, typename Unit>
			struct calculate_result
				: public sprout::identity<typename Image::result_type>
			{};
			template<typename Image, typename Unit>
			struct calculate_result<Image const, Unit>
				: public sprout::darkroom::materials::calculate_result<Image, Unit>
			{};
			template<typename Image, typename Unit>
			struct calculate_result<Image volatile, Unit>
				: public sprout::darkroom::materials::calculate_result<Image, Unit>
			{};
			template<typename Image, typename Unit>
			struct calculate_result<Image const volatile, Unit>
				: public sprout::darkroom::materials::calculate_result<Image, Unit>
			{};

			//
			// calculate
			//
			template<typename Image, typename Unit>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::materials::calculate_result<Image, Unit>::type
			calculate(Image const& image, Unit const& u, Unit const& v) {
				return image(u, v);
			}
		}	// namespace materials
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_MATERIALS_CALCULATE_HPP
