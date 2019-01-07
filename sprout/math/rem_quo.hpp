/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_REM_QUO_HPP
#define SPROUT_MATH_REM_QUO_HPP

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
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename R, typename FloatType, typename Pair>
			inline SPROUT_CONSTEXPR sprout::pair<FloatType, R>
			rem_quo_ret(Pair const& p) {
				typedef sprout::pair<FloatType, R> type;
				return type(static_cast<FloatType>(p.first), p.second);
			}

			template<typename R, typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, R>
			rem_quo_impl_7(T x, T y, int k, R iquo, T x1, T z) {
				typedef sprout::pair<T, R> type;
				return (z > y) || ((z == y) && ((iquo & 1) != 0))
					? x < 0 ? type(-(x1 - y), ((iquo + 1) & 0x7) * k) : type(x1 - y, ((iquo + 1) & 0x7) * k)
					: x < 0 ? type(-x1, (iquo & 0x7) * k) : type(x1, (iquo & 0x7) * k)
					;
			}
			template<typename R, typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, R>
			rem_quo_impl_6(T x, T y, int k, R iquo, T x1) {
				return x1 >= y
					? sprout::math::detail::rem_quo_impl_7(x, y, k, iquo + 1, x1 - y, (x1 - y) + (x1 - y))
					: sprout::math::detail::rem_quo_impl_7(x, y, k, iquo, x1, x1 + x1)
					;
			}
			template<typename R, typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, R>
			rem_quo_impl_5(T x, T y, int k, R iquo, T x1, T y1, T z, int iscy, int idiff, int i) {
				return i != idiff
					? z >= 0
						? sprout::math::detail::rem_quo_impl_5(x, y, k, iquo + iquo + 2, z + z, y1, z + z - y1, iscy, idiff, i + 1)
						: sprout::math::detail::rem_quo_impl_5(x, y, k, iquo + iquo, x1 + x1, y1, x1 + x1 - y1, iscy, idiff, i + 1)
					: sprout::math::detail::rem_quo_impl_6(x, y, k, iquo, sprout::math::scalbn(x1, iscy))
					;
			}
			template<typename R, typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, R>
			rem_quo_impl_4(T x, T y, int k, R iquo, T x1, T y1, int iscy, int idiff, int i) {
				return sprout::math::detail::rem_quo_impl_5(x, y, k, iquo, x1, y1, x1 - y1, iscy, idiff, i);
			}
			template<typename R, typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, R>
			rem_quo_impl_3(T x, T y, int k, R iquo, T x1, int iscx, int iscy, int idiff) {
				return idiff < 0 ? sprout::math::detail::rem_quo_impl_7(x, y, k, iquo, x1, x1 + x1)
					: idiff ? sprout::math::detail::rem_quo_impl_4(x, y, k, iquo, sprout::math::scalbn(x1, -iscx), sprout::math::scalbn(y, -iscy), iscy, idiff, 0)
					: sprout::math::detail::rem_quo_impl_6(x, y, k, iquo, x1)
					;
			}
			template<typename R, typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, R>
			rem_quo_impl_2(T x, T y, int k, R iquo, T x1, int iscx, int iscy) {
				return sprout::math::detail::rem_quo_impl_3(x, y, k, iquo, x1, iscx, iscy, iscx - iscy);
			}
			template<typename R, typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, R>
			rem_quo_impl_1(T x, T y, int k, R iquo, T x1) {
				return sprout::math::detail::rem_quo_impl_2(x, y, k, iquo, x1, sprout::math::ilogb(x1), sprout::math::ilogb(y));
			}
			template<typename R, typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, R>
			rem_quo_impl(T x, T y, R iquo) {
				return sprout::math::detail::rem_quo_impl_1(x, sprout::math::fabs(y), (sprout::math::signbit(x) ^ sprout::math::signbit(y) ? -1 : 1), iquo, sprout::math::fabs(x));
			}
		}	// namespace detail
		//
		// rem_quo
		//
		//
		// issue:
		//	rem_quo(-NaN, -NaN) returns {-NaN, _} .
		//		# returns {+NaN, _} . ( same as rem_quo(+NaN, +NaN) )
		//
		template<
			typename R = int,
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<R>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::pair<FloatType, R>
		rem_quo(FloatType x, FloatType y) {
			typedef sprout::pair<FloatType, R> type;
			return y == 0 ? type(-sprout::numeric_limits<FloatType>::quiet_NaN(), R(0))
				: sprout::math::isnan(y)
					? sprout::math::isnan(x)
						? type(sprout::math::signbit(y) && sprout::math::signbit(x) ? -sprout::numeric_limits<FloatType>::quiet_NaN() : sprout::numeric_limits<FloatType>::quiet_NaN(), R(0))
						: type(y, R(0))
				: sprout::math::isnan(x) ? type(x, R(0))
				: x == sprout::numeric_limits<FloatType>::infinity() || x == -sprout::numeric_limits<FloatType>::infinity()
					? type(-sprout::numeric_limits<FloatType>::quiet_NaN(), R(0))
				: x == 0 ? type(x, R(0))
				: y == sprout::numeric_limits<FloatType>::infinity() || y == -sprout::numeric_limits<FloatType>::infinity() ? type(x, R(0))
				: sprout::math::detail::rem_quo_ret<R, FloatType>(sprout::math::detail::rem_quo_impl(
					static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x),
					static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(y),
					R(0)
					))
				;
		}
		template<
			typename R = int,
			typename ArithmeticType1,
			typename ArithmeticType2,
			typename sprout::enabler_if<
				std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value && std::is_integral<R>::value
			>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR sprout::pair<
			typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type,
			R
		>
		rem_quo(ArithmeticType1 x, ArithmeticType2 y) {
			typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
			return sprout::math::rem_quo(static_cast<type>(x), static_cast<type>(y));
		}
	}	// namespace math

	using sprout::math::rem_quo;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_REM_QUO_HPP
