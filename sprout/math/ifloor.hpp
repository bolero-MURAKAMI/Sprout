/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_IFLOOR_HPP
#define SPROUT_MATH_IFLOOR_HPP

#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
#	include <sprout/math/floor.hpp>
#else
#	include <sprout/math/greater_equal.hpp>
#endif

namespace sprout {
	namespace math {
#if SPROUT_USE_BUILTIN_CMATH_FUNCTION
		namespace detail {
			template<typename To, typename FloatType>
			inline SPROUT_CONSTEXPR To
			ifloor_impl(FloatType x) {
				return sprout::numeric_limits<To>::max() < x || sprout::numeric_limits<To>::min() > x
						? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::runtime_error("ifloor: large float rounding."), static_cast<To>(x))
					: static_cast<To>(x)
					;
			}
		}	// namespace detail
		//
		// ifloor
		//
		template<
			typename To = int,
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<To>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR To
		ifloor(FloatType x) {
			return sprout::math::isnan(x) || sprout::math::isinf(x) ? sprout::numeric_limits<To>::min()
				: sprout::math::detail::ifloor_impl<To>(sprout::math::floor(x))
				;
		}
#else
		namespace detail {
			template<typename To, typename FloatType>
			inline SPROUT_CONSTEXPR To
			ifloor_impl(FloatType x, To x0) {
				return sprout::math::greater_equal(x, x0) ? x0
					: x0 - 1
					;
			}
		}	// namespace detail
		//
		// ifloor
		//
		template<
			typename To = int,
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<To>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR To
		ifloor(FloatType x) {
			return sprout::math::isnan(x) || sprout::math::isinf(x) ? sprout::numeric_limits<To>::min()
				: x == 0 ? To(0)
				: sprout::numeric_limits<To>::max() < x || sprout::numeric_limits<To>::min() > x
					? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::runtime_error("ifloor: large float rounding."), static_cast<To>(x))
				: sprout::math::detail::ifloor_impl(x, static_cast<To>(x))
				;
		}
#endif
		template<
			typename To = int,
			typename IntType,
			typename sprout::enabler_if<std::is_integral<IntType>::value && std::is_integral<To>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR To
		ifloor(IntType x) {
			return sprout::math::ifloor<To>(static_cast<double>(x));
		}
	}	// namespace math

	using sprout::math::ifloor;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_IFLOOR_HPP
