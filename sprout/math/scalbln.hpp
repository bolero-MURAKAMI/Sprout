#ifndef SPROUT_MATH_SCALBLN_HPP
#define SPROUT_MATH_SCALBLN_HPP

#include <cfloat>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			scalbln(FloatType x, long exp) {
				return static_cast<FloatType>(x * sprout::detail::pow_n(FloatType(FLT_RADIX), exp));
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			scalbln(IntType x, long exp) {
				return sprout::math::detail::scalbln(static_cast<double>(x), exp);
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::scalbln;
	}	// namespace math

	using sprout::math::scalbln;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SCALBLN_HPP
