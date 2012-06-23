#ifndef SPROUT_MATH_ISNAN_HPP
#define SPROUT_MATH_ISNAN_HPP

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
			inline SPROUT_CONSTEXPR int
			isnan(FloatType x) {
				return !(x == x);
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::isnan;
	}	// namespace math

	using sprout::math::isnan;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ISNAN_HPP
