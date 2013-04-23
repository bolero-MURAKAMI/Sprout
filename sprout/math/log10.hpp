#ifndef SPROUT_MATH_LOG10_HPP
#define SPROUT_MATH_LOG10_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			log10(FloatType x) {
				return x == 0 ? -std::numeric_limits<FloatType>::infinity()
					: x == 1 ? FloatType(0)
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: x < 0 ? std::numeric_limits<FloatType>::quiet_NaN()
					: sprout::log(x) / sprout::math::ln_ten<FloatType>()
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			log10(IntType x) {
				return sprout::math::detail::log10(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::log10;
	}	// namespace math

	using sprout::math::log10;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG10_HPP
