#ifndef SPROUT_MATH_CBRT_HPP
#define SPROUT_MATH_CBRT_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/pow.hpp>
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
			cbrt(FloatType x) {
				return x == 0 ? FloatType(0)
					: x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: x == -std::numeric_limits<FloatType>::infinity() ? -std::numeric_limits<FloatType>::infinity()
					: x < 0 ? -sprout::math::pow(-x, sprout::math::third<FloatType>())
					: sprout::math::pow(x, sprout::math::third<FloatType>())
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			cbrt(IntType x) {
				return sprout::math::detail::cbrt(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::cbrt;
	}	// namespace math

	using sprout::math::cbrt;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_CBRT_HPP
