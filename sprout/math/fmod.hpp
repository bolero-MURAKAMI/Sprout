/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_FMOD_HPP
#define SPROUT_MATH_FMOD_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/fabs.hpp>
#include <sprout/math/ilogb.hpp>
#include <sprout/math/scalbn.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			fmod_impl_6(T x, T y, T x1) {
				return x1 >= y
					? x < 0 ? -(x1 - y) : x1 - y
					: x < 0 ? -x1 : x1
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			fmod_impl_5(T x, T y, T x1, T y1, T z, int iscy, int idiff, int i) {
				return i != idiff
					? z >= 0
						? sprout::math::detail::fmod_impl_5(x, y, z + z, y1, z + z - y1, iscy, idiff, i + 1)
						: sprout::math::detail::fmod_impl_5(x, y, x1 + x1, y1, x1 + x1 - y1, iscy, idiff, i + 1)
					: sprout::math::detail::fmod_impl_6(x, y, sprout::math::scalbn(x1, iscy))
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			fmod_impl_4(T x, T y, T x1, T y1, int iscy, int idiff, int i) {
				return sprout::math::detail::fmod_impl_5(x, y, x1, y1, x1 - y1, iscy, idiff, i);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			fmod_impl_3(T x, T y, T x1, int iscx, int iscy, int idiff) {
				return idiff ? sprout::math::detail::fmod_impl_4(x, y, sprout::math::scalbn(x1, -iscx), sprout::math::scalbn(y, -iscy), iscy, idiff, 0)
					: sprout::math::detail::fmod_impl_6(x, y, x1)
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			fmod_impl_2(T x, T y, T x1, int iscx, int iscy) {
				return sprout::math::detail::fmod_impl_3(x, y, x1, iscx, iscy, iscx - iscy);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			fmod_impl_1(T x, T y, T x1) {
				return y > x1 ? x
					: sprout::math::detail::fmod_impl_2(x, y, x1, sprout::math::ilogb(x1), sprout::math::ilogb(y))
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			fmod_impl(T x, T y) {
				return sprout::math::detail::fmod_impl_1(x, sprout::math::fabs(y), sprout::math::fabs(x));
			}
		}	// namespace detail
		//
		// fmod
		//
		// issue:
		//	fmod(-NaN, -NaN) returns -NaN .
		//		# returns +NaN . ( same as fmod(+NaN, +NaN) )
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		fmod(FloatType x, FloatType y) {
			return sprout::math::isnan(y)
					? sprout::math::isnan(x)
						? sprout::math::signbit(y) || sprout::math::signbit(x) ? -sprout::numeric_limits<FloatType>::quiet_NaN()
							: sprout::numeric_limits<FloatType>::quiet_NaN()
						: y
				: sprout::math::isnan(x) ? x
				: x == sprout::numeric_limits<FloatType>::infinity() || x == -sprout::numeric_limits<FloatType>::infinity() || y == 0
					? -sprout::numeric_limits<FloatType>::quiet_NaN()
				: x == 0 ? x
				: y == sprout::numeric_limits<FloatType>::infinity() || y == -sprout::numeric_limits<FloatType>::infinity() ? x
				: static_cast<FloatType>(sprout::math::detail::fmod_impl(
					static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x),
					static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(y)
					))
				;
		}

		template<
			typename ArithmeticType1,
			typename ArithmeticType2,
			typename sprout::enabler_if<
				std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type
		fmod(ArithmeticType1 x, ArithmeticType2 y) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::fmod(static_cast<type>(x), static_cast<type>(y));
		}
	}	// namespace math

	using sprout::math::fmod;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FMOD_HPP
