#ifndef SPROUT_MATH_LLROUND_HPP
#define SPROUT_MATH_LLROUND_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/iround.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR long long
			llround(FloatType x) {
				return sprout::iround<long long>(x);
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR long long
			llround(IntType x) {
				return sprout::iround<long long>(x);
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::llround;
	}	// namespace math

	using sprout::math::llround;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LLROUND_HPP
