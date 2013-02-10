#ifndef SPROUT_MATH_FLOAT2_SIG_EXP_HPP
#define SPROUT_MATH_FLOAT2_SIG_EXP_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/float2_exponent.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, int>
			float2_sig_exp_impl(T x, int exp) {
				return sprout::pair<T, int>(x / sprout::detail::pow_n(T(2), exp), exp);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::pair<FloatType, int>
			float2_sig_exp(FloatType x) {
				return sprout::math::detail::float2_sig_exp_impl(x, sprout::math::float2_exponent(x));
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::pair<double, int>
			float2_sig_exp(IntType x) {
				return sprout::math::detail::float2_sig_exp(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::float2_sig_exp;
	}	// namespace math

	using sprout::math::float2_sig_exp;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FLOAT2_SIG_EXP_HPP
