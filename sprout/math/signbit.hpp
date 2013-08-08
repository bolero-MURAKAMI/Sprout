/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_SIGNBIT_HPP
#define SPROUT_MATH_SIGNBIT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			signbit(FloatType x) {
				return !sprout::math::isnan(x) && x < 0;
			}
		}	// namespace detail
		//
		// issue:
		//	[ !SPROUT_USE_BUILTIN_CMATH_FUNCTION ]
		//	signbit(-0) returns false .
		//		# returns true . ( same as signbit(+0) )
		//	signbit(-NaN) returns false .
		//		# returns true . ( same as signbit(+NaN) )
		//
		using NS_SPROUT_MATH_DETAIL::signbit;
	}	// namespace math

	using sprout::math::signbit;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SIGNBIT_HPP
