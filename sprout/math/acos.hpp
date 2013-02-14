#ifndef SPROUT_MATH_ACOS_HPP
#define SPROUT_MATH_ACOS_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/asin.hpp>
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
			acos(FloatType x) {
				return x == 1 ? FloatType(0)
					: x > 1 || x < -1 ? std::numeric_limits<FloatType>::quiet_NaN()
					: sprout::math::half_pi<FloatType>() - sprout::math::asin(x)
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			acos(IntType x) {
				return sprout::math::detail::acos(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::acos;
	}	// namespace math

	using sprout::math::acos;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ACOS_HPP
