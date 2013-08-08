/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_TRUNC_HPP
#define SPROUT_MATH_TRUNC_HPP

#include <cstdint>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
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
			inline SPROUT_CONSTEXPR FloatType
			trunc(FloatType x) {
				return sprout::math::isnan(x) ? x
					: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
					: x == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::numeric_limits<FloatType>::infinity()
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
					: std::trunc(x)
#else
					: x == 0 ? x
					: sprout::numeric_limits<std::uintmax_t>::max() < x || sprout::numeric_limits<std::uintmax_t>::max() < -x
						? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::runtime_error("trunc: large float rounding."), x)
					: x < 0 ? -static_cast<FloatType>(static_cast<std::uintmax_t>(-x))
					: static_cast<FloatType>(static_cast<std::uintmax_t>(x))
#endif
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			trunc(IntType x) {
				return sprout::math::detail::trunc(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::trunc;
	}	// namespace math

	using sprout::math::trunc;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_TRUNC_HPP
