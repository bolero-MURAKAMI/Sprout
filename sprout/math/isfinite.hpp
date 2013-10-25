/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ISFINITE_HPP
#define SPROUT_MATH_ISFINITE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			template<typename FloatType>
			inline SPROUT_CONSTEXPR bool
			builtin_isfinite(FloatType x) {
				return __builtin_isfinite(x);
			}
#endif
		}	// namespace detail
		//
		// isfinite
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		isfinite(FloatType x) {
			return
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
				sprout::math::detail::builtin_isfinite(x)
#else
				!(sprout::math::isnan(x) || sprout::math::isinf(x))
#endif
				;
		}
		template<
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		isfinite(IntType x) {
			return true;
		}
	}	// namespace math

	using sprout::math::isfinite;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ISFINITE_HPP
