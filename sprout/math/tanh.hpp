#ifndef SPROUT_MATH_TANH_HPP
#define SPROUT_MATH_TANH_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/sinh.hpp>
#include <sprout/math/cosh.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			tanh(FloatType x) {
				return sprout::math::sinh(x) / sprout::math::cosh(x);
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			tanh(IntType x) {
				return sprout::math::detail::tanh(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::tanh;
	}	// namespace math

	using sprout::math::tanh;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_TANH_HPP
