#ifndef SPROUT_MATH_IS_EVEN_HPP
#define SPROUT_MATH_IS_EVEN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/fmod.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			is_even(FloatType x) {
				return sprout::math::fmod(x, FloatType(2)) == FloatType(0);
			}
		}	// namespace detail

		using sprout::math::detail::is_even;
	}	// namespace math

	using sprout::math::is_even;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_IS_EVEN_HPP
