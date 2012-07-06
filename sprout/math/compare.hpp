#ifndef SPROUT_MATH_COMPARE_HPP
#define SPROUT_MATH_COMPARE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/equal_to.hpp>
#include <sprout/math/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR int
			compare_impl(T x, T y) {
				return sprout::math::equal_to(x, y) ? 0
					: x < y ? -1
					: 1
					;
			}
		}	// namespace detail
		//
		// compare
		//
		template<
			typename T1,
			typename T2,
			typename sprout::enabler_if<std::is_arithmetic<T1>::value && std::is_arithmetic<T2>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR int
		compare(T1 x, T2 y) {
			typedef typename sprout::math::float_promote<T1, T2>::type promoted;
			return sprout::math::detail::compare_impl<promoted>(x, y);
		}
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_COMPARE_HPP
