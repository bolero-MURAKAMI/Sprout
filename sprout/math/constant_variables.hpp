/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_CONSTANT_VARIABLES_HPP
#define SPROUT_MATH_CONSTANT_VARIABLES_HPP

#include <sprout/config.hpp>
#if SPROUT_USE_VARIABLE_TEMPLATES
#	include <sprout/math/constants.hpp>
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES

namespace sprout {
	namespace math {
#if SPROUT_USE_VARIABLE_TEMPLATES
		//
		// pi
		//
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T pi_v = sprout::math::pi<T>();
		//
		// half_pi
		//
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T half_pi_v = sprout::math::half_pi<T>();
		//
		// third_pi
		// two_thirds_pi
		//
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T third_pi_v = sprout::math::third_pi<T>();
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T two_thirds_pi_v = sprout::math::two_thirds_pi<T>();
		//
		// quarter_pi
		// three_quarters_pi
		//
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T quarter_pi_v = sprout::math::quarter_pi<T>();
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T three_quarters_pi_v = sprout::math::three_quarters_pi<T>();
		//
		// two_pi
		// four_pi
		//
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T two_pi_v = sprout::math::two_pi<T>();
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T four_pi_v = sprout::math::four_pi<T>();
		//
		// two_div_pi
		// root_two_div_pi
		//
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T two_div_pi_v = sprout::math::two_div_pi<T>();
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T root_two_div_pi_v = sprout::math::root_two_div_pi<T>();
		//
		// root_pi
		// one_div_root_pi
		// root_one_div_pi
		// two_div_root_pi
		//
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T root_pi_v = sprout::math::root_pi<T>();
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T one_div_root_pi_v = sprout::math::one_div_root_pi<T>();
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T root_one_div_pi_v = sprout::math::root_one_div_pi<T>();
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T two_div_root_pi_v = sprout::math::two_div_root_pi<T>();
		//
		// half
		// quarter
		// third
		// two_thirds
		//
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T half_v = sprout::math::half<T>();
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T quarter_v = sprout::math::quarter<T>();
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T third_v = sprout::math::third<T>();
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T two_thirds_v = sprout::math::two_thirds<T>();
		//
		// root_two
		// root_three
		// half_root_two
		//
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T root_two_v = sprout::math::root_two<T>();
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T root_three_v = sprout::math::root_three<T>();
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T half_root_two_v = sprout::math::half_root_two<T>();
		//
		// e
		//
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T e_v = sprout::math::e<T>();
		//
		// ln_ten
		// ln_two
		//
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T ln_ten_v = sprout::math::ln_ten<T>();
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T ln_two_v = sprout::math::ln_two<T>();
		//
		// phi
		//
		template<typename T>
		SPROUT_STATIC_CONSTEXPR T phi_v = sprout::math::phi<T>();
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_CONSTANT_VARIABLES_HPP
