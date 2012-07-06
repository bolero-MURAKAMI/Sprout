#ifndef SPROUT_MATH_NOT_EQUAL_TO_HPP
#define SPROUT_MATH_NOT_EQUAL_TO_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/equal_to.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		//
		// not_equal_to
		//
		template<
			typename T1,
			typename T2,
			typename sprout::enabler_if<std::is_arithmetic<T1>::value && std::is_arithmetic<T2>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		not_equal_to(T1 x, T2 y) {
			return !sprout::math::equal_to(x, y);
		}
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_NOT_EQUAL_TO_HPP
