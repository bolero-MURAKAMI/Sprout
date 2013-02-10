#ifndef SPROUT_MATH_LROUND_HPP
#define SPROUT_MATH_LROUND_HPP

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
			inline SPROUT_CONSTEXPR long
			lround(FloatType x) {
				return sprout::math::iround<long>(x);
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR long
			lround(IntType x) {
				return sprout::math::iround<long>(x);
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::lround;
	}	// namespace math

	using sprout::math::lround;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LROUND_HPP
