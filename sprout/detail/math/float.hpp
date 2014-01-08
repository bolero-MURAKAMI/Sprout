/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_FLOAT_HPP
#define SPROUT_DETAIL_FLOAT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/abs.hpp>
#include <sprout/math/floor.hpp>
#include <sprout/math/round.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/utility/pair/pair.hpp>
#include <sprout/detail/pow.hpp>

namespace sprout {
	namespace detail {
		//
		// float_pow10
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		float_pow10(int exponent) {
			return sprout::detail::pow_n(FloatType(10), exponent);
		}

		//
		// float_exponent10
		//
		template<typename FloatType>
		inline SPROUT_CONSTEXPR sprout::pair<int, FloatType>
		float_exponent10_positive_1(sprout::pair<int, FloatType> const& current, int n) {
			typedef sprout::pair<int, FloatType> type;
			return (current.second) < 10 ? current
				: n == 1 ? type(current.first + 1, current.second / 10)
				: sprout::detail::float_exponent10_positive_1(
					sprout::detail::float_exponent10_positive_1(
						current,
						n / 2
						),
					n - n / 2
					)
				;
		}
		template<typename FloatType>
		inline SPROUT_CONSTEXPR sprout::pair<int, FloatType>
		float_exponent10_positive_0(sprout::pair<int, FloatType> const& current, int n) {
			return (current.second) < 10 ? current
				: sprout::detail::float_exponent10_positive_0(
					sprout::detail::float_exponent10_positive_1(
						current,
						n
						),
					n * 2
					)
				;
		}
		template<typename FloatType>
		inline SPROUT_CONSTEXPR int
		float_exponent10_positive(FloatType val) {
			typedef sprout::pair<int, FloatType> type;
			return float_exponent10_positive_0(type(val, 0), 1).first;
		}
		template<typename FloatType>
		inline SPROUT_CONSTEXPR sprout::pair<int, FloatType>
		float_exponent10_negative_1(sprout::pair<int, FloatType> const& current, int n) {
			typedef sprout::pair<int, FloatType> type;
			return !((current.second) < 1) ? current
				: n == 1 ? type(current.first + 1, current.second * 10)
				: sprout::detail::float_exponent10_negative_1(
					sprout::detail::float_exponent10_negative_1(
						current,
						n / 2
						),
					n - n / 2
					)
				;
		}
		template<typename FloatType>
		inline SPROUT_CONSTEXPR sprout::pair<int, FloatType>
		float_exponent10_negative_0(sprout::pair<int, FloatType> const& current, int n) {
			return !((current.second) < 1) ? current
				: sprout::detail::float_exponent10_negative_0(
					sprout::detail::float_exponent10_negative_1(
						current,
						n
						),
					n * 2
					)
				;
		}
		template<typename FloatType>
		inline SPROUT_CONSTEXPR int
		float_exponent10_negative(FloatType val) {
			typedef sprout::pair<int, FloatType> type;
			return float_exponent10_negative_0(type(val, 0), 1).first;
		}
		// !!! OLD:
//		template<typename FloatType>
//		inline SPROUT_CONSTEXPR int
//		float_exponent10_positive(FloatType val) {
//			return val < 10 ? 0
//				: 1 + sprout::detail::float_exponent10_positive(val / 10)
//				;
//		}
//		template<typename FloatType>
//		inline SPROUT_CONSTEXPR int
//		float_exponent10_negative(FloatType val) {
//			return val < 1 ? 1 + sprout::detail::float_exponent10_negative(val * 10)
//				: 0
//				;
//		}
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		float_exponent10(FloatType val) {
			return val < 0
				? val > -1
					? sprout::detail::float_exponent10_negative(-val)
					: sprout::detail::float_exponent10_positive(-val)
				: val < 1
					? sprout::detail::float_exponent10_negative(val)
					: sprout::detail::float_exponent10_positive(val)
				;
		}

		//
		// float_digit_at
		//
		template<typename FloatType>
		inline SPROUT_CONSTEXPR int
		float_digit_of_impl(FloatType val) {
			return static_cast<int>((val - sprout::math::floor(val)) * 10);
		}
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		float_digit_at(FloatType val, int digits) {
			return sprout::detail::float_digit_of_impl(val / sprout::detail::float_pow10<FloatType>(digits + 1));
		}

		//
		// float_digits
		//
		template<typename FloatType>
		inline SPROUT_CONSTEXPR sprout::pair<int, FloatType>
		float_digits_impl_1(sprout::pair<int, FloatType> const& current, FloatType val, int n) {
			typedef sprout::pair<int, FloatType> type;
			return (val / current.second) < 1 ? current
				: n == 1 ? type(current.first + 1, current.second * FloatType(10))
				: sprout::detail::float_digits_impl_1(
					sprout::detail::float_digits_impl_1(
						current,
						val, n / 2
						),
					val, n - n / 2
					)
				;
		}
		template<typename FloatType>
		inline SPROUT_CONSTEXPR sprout::pair<int, FloatType>
		float_digits_impl(sprout::pair<int, FloatType> const& current, FloatType val, int n) {
			return (val / current.second) < 1 ? current
				: sprout::detail::float_digits_impl(
					sprout::detail::float_digits_impl_1(
						current,
						val, n
						),
					val, n * 2
					)
				;
		}
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		float_digits(FloatType val) {
			typedef sprout::pair<int, FloatType> type;
			return val < 0
				? val > -1 ? 1 : sprout::detail::float_digits_impl(type(1, FloatType(10)), -val, 1).first
				: val < 1 ? 1 : sprout::detail::float_digits_impl(type(1, FloatType(10)), val, 1).first
				;
		}

		//
		// float_digits_checked
		//
		template<typename FloatType>
		inline SPROUT_CONSTEXPR int
		float_digits_checked_impl(FloatType val, int digits) {
			return val == 0 ? digits
				: sprout::detail::float_digit_at(val, digits - 1) == 0 ? digits - 1 : digits
				;
		}
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		float_digits_checked(FloatType val) {
			return sprout::detail::float_digits_checked_impl(val, sprout::detail::float_digits(val));
		}

		//
		// float_round_at
		//
		template<typename FloatType>
		inline SPROUT_CONSTEXPR FloatType
		float_round_impl(FloatType val, FloatType p10) {
			return sprout::math::round(val * p10) / p10;
		}
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR FloatType
		float_round_at(FloatType val, int digits) {
			return sprout::detail::float_round_impl(val, sprout::detail::float_pow10<FloatType>(digits));
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_FLOAT_HPP
