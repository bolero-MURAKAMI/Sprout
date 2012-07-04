#ifndef SPROUT_DETAIL_FLOAT_HPP
#define SPROUT_DETAIL_FLOAT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/abs.hpp>
#include <sprout/math/floor.hpp>
#include <sprout/math/round.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace detail {
		//
		// float_pow10
		//
		template<typename FloatType>
		inline SPROUT_CONSTEXPR FloatType
		float_pow10_positive(int exponent) {
			return exponent ? sprout::detail::float_pow10_positive<FloatType>(exponent - 1) * 10
				: FloatType(1)
				;
		}
		template<typename FloatType>
		inline SPROUT_CONSTEXPR FloatType
		float_pow10_negative(int exponent) {
			return exponent ? sprout::detail::float_pow10_negative<FloatType>(exponent + 1) / 10
				: FloatType(1)
				;
		}
		template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
		inline SPROUT_CONSTEXPR FloatType
		float_pow10(int exponent) {
			return exponent < 0
				? sprout::detail::float_pow10_negative<FloatType>(exponent)
				: sprout::detail::float_pow10_positive<FloatType>(exponent)
				;
		}

		//
		// float_exponent10
		//
		template<typename FloatType>
		inline SPROUT_CONSTEXPR int
		float_exponent10_positive(FloatType val) {
			return val < 10 ? 0
				: 1 + sprout::detail::float_exponent10_positive(val / 10)
				;
		}
		template<typename FloatType>
		inline SPROUT_CONSTEXPR int
		float_exponent10_negative(FloatType val) {
			return val < 1 ? 1 + sprout::detail::float_exponent10_negative(val * 10)
				: 0
				;
		}
		template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
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
		// float_digits
		//
		template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
		inline SPROUT_CONSTEXPR int
		float_digits_impl(FloatType val) {
			return val < 1 ? 0
				: 1 + sprout::detail::float_digits_impl(val / 10)
				;
		}
		template<typename FloatType>
		inline SPROUT_CONSTEXPR int
		float_digits(FloatType val) {
			return val < 0
				? val > -1 ? 1 : 1 + sprout::detail::float_digits_impl(-val / 10)
				: val < 1 ? 1 : 1 + sprout::detail::float_digits_impl(val / 10)
				;
		}

		//
		// float_digit_at
		//
		template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
		inline SPROUT_CONSTEXPR int
		float_digit_of_impl(FloatType val) {
			using sprout::floor;
			return static_cast<int>((val - floor(val)) * 10);
		}
		template<typename FloatType>
		inline SPROUT_CONSTEXPR int
		float_digit_at(FloatType val, int digits) {
			return sprout::detail::float_digit_of_impl(val / sprout::detail::float_pow10<FloatType>(digits + 1));
		}

		//
		// float_round_at
		//
		template<typename FloatType, typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler>
		inline SPROUT_CONSTEXPR FloatType
		float_round_impl(FloatType val, FloatType p10) {
			using sprout::round;
			return round(val * p10) / p10;
		}
		template<typename FloatType>
		inline SPROUT_CONSTEXPR FloatType
		float_round_at(FloatType val, int digits) {
			return sprout::detail::float_round_impl(val, sprout::detail::float_pow10<FloatType>(digits));
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_FLOAT_HPP
