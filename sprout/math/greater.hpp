#ifndef SPROUT_MATH_GREATER_HPP
#define SPROUT_MATH_GREATER_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/not_equal_to.hpp>
#include <sprout/math/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			greater(FloatType x, FloatType y) {
				return sprout::math::not_equal_to(x, y) && x > y;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			greater(IntType x, IntType y) {
				return x > y;
			}
		}	// namespace detail
		//
		// greater
		//
		template<
			typename T1,
			typename T2,
			typename sprout::enabler_if<std::is_arithmetic<T1>::value && std::is_arithmetic<T2>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		greater(T1 x, T2 y) {
			typedef typename sprout::math::float_promote<T1, T2>::type promoted;
			return sprout::math::detail::greater<promoted>(x, y);
		}
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_GREATER_HPP
