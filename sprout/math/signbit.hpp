#ifndef SPROUT_MATH_SIGNBIT_HPP
#define SPROUT_MATH_SIGNBIT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			signbit(FloatType x) {
				return x < 0;
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::signbit;
	}	// namespace math

	using sprout::math::signbit;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SIGNBIT_HPP
