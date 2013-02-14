#ifndef SPROUT_MATH_ERFC_HPP
#define SPROUT_MATH_ERFC_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/erf.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			erfc(FloatType x) {
				return x == std::numeric_limits<FloatType>::infinity() ? FloatType(0)
					: x == -std::numeric_limits<FloatType>::infinity() ? FloatType(2)
					: FloatType(1) - sprout::math::erf(x)
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			erfc(IntType x) {
				return sprout::math::detail::erfc(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::erfc;
	}	// namespace math

	using sprout::math::erfc;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ERFC_HPP
