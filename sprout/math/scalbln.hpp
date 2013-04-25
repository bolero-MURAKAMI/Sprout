#ifndef SPROUT_MATH_SCALBLN_HPP
#define SPROUT_MATH_SCALBLN_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename FloatType, typename T>
			inline SPROUT_CONSTEXPR T
			scalbln_impl(T x, long exp) {
				return x * sprout::detail::pow_n(T(std::numeric_limits<FloatType>::radix), exp);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			scalbln(FloatType x, long exp) {
				return x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: x == -std::numeric_limits<FloatType>::infinity() ? -std::numeric_limits<FloatType>::infinity()
					: exp == 0 ? x
					: x == 0 ? x
					: static_cast<FloatType>(sprout::math::detail::scalbln_impl<FloatType>(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x), exp))
					;
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
