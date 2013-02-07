#ifndef SPROUT_MATH_LOGB_HPP
#define SPROUT_MATH_LOGB_HPP

#include <climits>
#include <cfloat>
#include <cstdint>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/log_a.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_2_neg_lo(T x, T x0, T base, T exp) {
				return base < 1 ? sprout::math::detail::logb_impl_2_neg_lo(x, x0 * FLT_RADIX, x / (x0 / FLT_RADIX), exp - 1)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_2_neg_hi(T x, T x0, T base, T exp) {
				return !(base < FLT_RADIX) ? sprout::math::detail::logb_impl_2_neg_hi(x, x0 / FLT_RADIX, x / (x0 * FLT_RADIX), exp + 1)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_2_pos_lo(T x, T x0, T base, T exp) {
				return base < 1 ? sprout::math::detail::logb_impl_2_pos_lo(x, x0 * FLT_RADIX, x / (x0 / FLT_RADIX), exp + 1)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_2_pos_hi(T x, T x0, T base, T exp) {
				return !(base < FLT_RADIX) ? sprout::math::detail::logb_impl_2_pos_hi(x, x0 / FLT_RADIX, x / (x0 * FLT_RADIX), exp - 1)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_2(T x, T x0, T base, T exp) {
				return exp < 0
					? base < 1 ? sprout::math::detail::logb_impl_2_neg_lo(x, x0 * FLT_RADIX, x / (x0 / FLT_RADIX), exp - 1)
						: !(base < FLT_RADIX) ? sprout::math::detail::logb_impl_2_neg_hi(x, x0 / FLT_RADIX, x / (x0 * FLT_RADIX), exp + 1)
						: exp
					: base < 1 ? sprout::math::detail::logb_impl_2_pos_lo(x, x0 * FLT_RADIX, x / (x0 / FLT_RADIX), exp + 1)
						: !(base < FLT_RADIX) ? sprout::math::detail::logb_impl_2_pos_hi(x, x0 / FLT_RADIX, x / (x0 * FLT_RADIX), exp - 1)
						: exp
						;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_1(T x, T x0, T exp) {
				return sprout::math::detail::logb_impl_2(x, x0, x / x0, exp);
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl(T x, T exp) {
				return std::numeric_limits<std::intmax_t>::max() < exp || std::numeric_limits<std::intmax_t>::min() > exp
					? SPROUT_MATH_THROW_LARGE_FLOAT_ROUNDING(std::domain_error("trunc: large float rounding."), exp)
					: sprout::math::detail::logb_impl_1(
						x, sprout::detail::pow_n(T(FLT_RADIX), static_cast<std::intmax_t>(exp)),
						static_cast<T>(static_cast<std::intmax_t>(exp))
						)
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			logb(FloatType x) {
				return x < 0 ? sprout::math::detail::logb_impl(-x, sprout::math::trunc(sprout::math::log_a(FloatType(FLT_RADIX), -x)))
					: sprout::math::detail::logb_impl(x, sprout::math::trunc(sprout::math::log_a(FloatType(FLT_RADIX), x)))
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			logb(IntType x) {
				return sprout::math::detail::logb(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::logb;
	}	// namespace math

	using sprout::math::logb;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOGB_HPP
