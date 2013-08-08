/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ICEIL_HPP
#define SPROUT_MATH_ICEIL_HPP

#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <sprout/math/ceil.hpp>
#else
#	include <sprout/math/less_equal.hpp>
#endif

namespace sprout {
	namespace math {
		namespace detail {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
			template<typename To, typename FloatType>
			inline SPROUT_CONSTEXPR To
			iceil_impl(FloatType x) {
				return sprout::numeric_limits<To>::max() < x || sprout::numeric_limits<To>::min() > x
						? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::runtime_error("iceil: large float rounding."), static_cast<To>(x))
					: static_cast<To>(x)
					;
			}
			template<
				typename To = int,
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<To>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR To
			iceil(FloatType x) {
				return sprout::math::isnan(x) || sprout::math::isinf(x) ? sprout::numeric_limits<To>::min()
					: sprout::math::detail::iceil_impl<To>(sprout::math::ceil(x))
					;
			}
#else
			template<typename To, typename FloatType>
			inline SPROUT_CONSTEXPR To
			iceil_impl(FloatType x, To x0) {
				return sprout::math::less_equal(x, x0) ? x0
					: x0 + 1
					;
			}
			template<
				typename To = int,
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<To>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR To
			iceil(FloatType x) {
				return sprout::math::isnan(x) || sprout::math::isinf(x) ? sprout::numeric_limits<To>::min()
					: x == 0 ? To(0)
					: sprout::numeric_limits<To>::max() < x || sprout::numeric_limits<To>::min() > x
						? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::runtime_error("iceil: large float rounding."), static_cast<To>(x))
					: sprout::math::detail::iceil_impl(x, static_cast<To>(x))
					;
			}
#endif
			template<
				typename To = int,
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value && std::is_integral<To>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR To
			iceil(IntType x) {
				return sprout::math::detail::iceil<To>(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::iceil;
	}	// namespace math

	using sprout::math::iceil;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ICEIL_HPP
