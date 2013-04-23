#ifndef SPROUT_MATH_LOG1P_HPP
#define SPROUT_MATH_LOG1P_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/log.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			log1p(FloatType x) {
				return x == 0 ? FloatType(0)
					: x == -1 ? -std::numeric_limits<FloatType>::infinity()
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: x < -1 ? std::numeric_limits<FloatType>::quiet_NaN()
					: sprout::log(1 + x)
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			log1p(IntType x) {
				return sprout::math::detail::log1p(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::log1p;
	}	// namespace math

	using sprout::math::log1p;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG1P_HPP
