/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_IROUND_HPP
#define SPROUT_MATH_IROUND_HPP

#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <sprout/math/round.hpp>
#else
#	include <sprout/math/equal_to.hpp>
#endif

namespace sprout {
	namespace math {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		namespace detail {
			template<typename To, typename FloatType>
			inline SPROUT_CONSTEXPR To
			iround_impl(FloatType x) {
				return sprout::numeric_limits<To>::max() < x || sprout::numeric_limits<To>::min() > x
						? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::runtime_error("iround: large float rounding."), static_cast<To>(x))
					: static_cast<To>(x)
					;
			}
		}	// namespace detail
		//
		// iround
		//
		template<
			typename To = int,
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<To>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR To
		iround(FloatType x) {
			return sprout::math::isnan(x) || sprout::math::isinf(x) ? sprout::numeric_limits<To>::min()
				: sprout::math::detail::iround_impl<To>(sprout::math::round(x))
				;
		}
#else
		namespace detail {
			template<typename To, typename FloatType>
			inline SPROUT_CONSTEXPR To
			iround_impl_positive(FloatType x, To x0) {
				return x - x0 < FloatType(0.5) ? x0
					: x0 + 1
					;
			}
			template<typename To, typename FloatType>
			inline SPROUT_CONSTEXPR To
			iround_impl_nagative(FloatType x, To x0) {
				return x0 - x < FloatType(0.5) ? x0
					: x0 - 1
					;
			}
		}	// namespace detail
		//
		// iround
		//
		template<
			typename To = int,
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<To>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR To
		iround(FloatType x) {
			return sprout::math::isnan(x) || sprout::math::isinf(x) ? sprout::numeric_limits<To>::min()
				: x == 0 ? To(0)
				: sprout::numeric_limits<To>::max() < x || sprout::numeric_limits<To>::min() > x
					? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::runtime_error("iround: large float irounding."), x)
				: x < 0 ? sprout::math::detail::iround_impl_nagative(x, static_cast<To>(x))
				: sprout::math::detail::iround_impl_positive(x, static_cast<To>(x))
				;
		}
#endif
		template<
			typename To = int,
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value && std::is_integral<To>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR To
		iround(IntType x) {
			return sprout::math::iround(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::iround;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_IROUND_HPP
