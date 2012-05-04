#ifndef SPROUT_MATH_EXP10_HPP
#define SPROUT_MATH_EXP10_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/exp.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/utility/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			exp10(FloatType x) {
				return sprout::math::detail::exp(x * sprout::math::ln_ten<FloatType>());
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			exp10(IntType x) {
				return sprout::math::detail::exp10(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::exp10;
	}	// namespace math

	using sprout::math::exp10;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_EXP10_HPP
