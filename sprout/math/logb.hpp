#ifndef SPROUT_MATH_LOGB_HPP
#define SPROUT_MATH_LOGB_HPP

#include <cstdint>
#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/log_a.hpp>
#include <sprout/math/trunc.hpp>
#include <sprout/math/itrunc.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_2_neg_lo(T x, T x0, T base, T exp) {
				return base < 1 ? sprout::math::detail::logb_impl_2_neg_lo(
						x, x0 * std::numeric_limits<T>::radix, x / (x0 / std::numeric_limits<T>::radix), exp - 1
						)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_2_neg_hi(T x, T x0, T base, T exp) {
				return !(base < std::numeric_limits<T>::radix) ? sprout::math::detail::logb_impl_2_neg_hi(
						x, x0 / std::numeric_limits<T>::radix, x / (x0 * std::numeric_limits<T>::radix), exp + 1
						)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_2_pos_lo(T x, T x0, T base, T exp) {
				return base < 1 ? sprout::math::detail::logb_impl_2_pos_lo(
						x, x0 * std::numeric_limits<T>::radix, x / (x0 / std::numeric_limits<T>::radix), exp + 1
						)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_2_pos_hi(T x, T x0, T base, T exp) {
				return !(base < std::numeric_limits<T>::radix) ? sprout::math::detail::logb_impl_2_pos_hi(
						x, x0 / std::numeric_limits<T>::radix, x / (x0 * std::numeric_limits<T>::radix), exp - 1
						)
					: exp
					;
			}
			template<typename T>
			inline SPROUT_CONSTEXPR T
			logb_impl_2(T x, T x0, T base, T exp) {
				return exp < 0
					? base < 1 ? sprout::math::detail::logb_impl_2_neg_lo(
							x, x0 * std::numeric_limits<T>::radix, x / (x0 / std::numeric_limits<T>::radix), exp - 1
							)
						: !(base < std::numeric_limits<T>::radix) ? sprout::math::detail::logb_impl_2_neg_hi(
							x, x0 / std::numeric_limits<T>::radix, x / (x0 * std::numeric_limits<T>::radix), exp + 1
							)
						: exp
					: base < 1 ? sprout::math::detail::logb_impl_2_pos_lo(
							x, x0 * std::numeric_limits<T>::radix, x / (x0 / std::numeric_limits<T>::radix), exp + 1
							)
						: !(base < std::numeric_limits<T>::radix) ? sprout::math::detail::logb_impl_2_pos_hi(
							x, x0 / std::numeric_limits<T>::radix, x / (x0 * std::numeric_limits<T>::radix), exp - 1
							)
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
				return sprout::math::detail::logb_impl_1(
					x, sprout::detail::pow_n(T(std::numeric_limits<T>::radix), sprout::itrunc<std::intmax_t>(exp)), exp
					);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			logb(FloatType x) {
				return x == 0 ? -std::numeric_limits<FloatType>::infinity()
					: x == std::numeric_limits<FloatType>::infinity() || x == -std::numeric_limits<FloatType>::infinity()
						? std::numeric_limits<FloatType>::infinity()
					: x < 0 ? sprout::math::detail::logb_impl(-x, sprout::trunc(sprout::log_a(FloatType(std::numeric_limits<FloatType>::radix), -x)))
					: sprout::math::detail::logb_impl(x, sprout::trunc(sprout::log_a(FloatType(std::numeric_limits<FloatType>::radix), x)))
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
