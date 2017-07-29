/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_CAMERAS_CALCULATE_HPP
#define SPROUT_DARKROOM_CAMERAS_CALCULATE_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace darkroom {
		namespace cameras {
			//
			// calculate_result
			//
			template<typename Camera, typename Unit2D>
			struct calculate_result
				: public sprout::identity<typename Camera::ray_type>
			{};
			template<typename Camera, typename Unit2D>
			struct calculate_result<Camera const, Unit2D>
				: public sprout::darkroom::cameras::calculate_result<Camera, Unit2D>
			{};
			template<typename Camera, typename Unit2D>
			struct calculate_result<Camera volatile, Unit2D>
				: public sprout::darkroom::cameras::calculate_result<Camera, Unit2D>
			{};
			template<typename Camera, typename Unit2D>
			struct calculate_result<Camera const volatile, Unit2D>
				: public sprout::darkroom::cameras::calculate_result<Camera, Unit2D>
			{};

			//
			// calculate
			//
			template<typename Camera, typename Unit2D>
			inline SPROUT_CONSTEXPR typename sprout::darkroom::cameras::calculate_result<Camera, Unit2D>::type
			calculate(Camera const& camera, Unit2D const& x, Unit2D const& y, Unit2D const& width, Unit2D const& height) {
				return camera(x, y, width, height);
			}
		}	// namespace cameras
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_CAMERAS_CALCULATE_HPP
