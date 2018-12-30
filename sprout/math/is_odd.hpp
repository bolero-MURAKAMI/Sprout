/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_IS_ODD_HPP
#define SPROUT_MATH_IS_ODD_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/isfinite.hpp>
#include <sprout/math/fmod.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR bool
			is_odd_unchecked(T x) {
				return sprout::math::fmod(x, T(2)) == T(1);
			}
		}	// namespace detail
		//
		// is_odd
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		is_odd(FloatType x) {
			return sprout::math::isfinite(x)
				&& sprout::math::detail::is_odd_unchecked(x < 0 ? -x : x)
				;
		}
	}	// namespace math

	using sprout::math::is_odd;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_IS_ODD_HPP
