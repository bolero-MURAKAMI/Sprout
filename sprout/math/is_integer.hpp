#ifndef SPROUT_MATH_IS_INTEGER_HPP
#define SPROUT_MATH_IS_INTEGER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/trunc.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			is_integer(FloatType x) {
				return x == sprout::math::trunc(x);
			}
		}	// namespace detail

		using sprout::math::detail::is_integer;
	}	// namespace math

	using sprout::math::is_integer;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_IS_INTEGER_HPP
