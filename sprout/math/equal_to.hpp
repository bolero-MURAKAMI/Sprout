#ifndef SPROUT_MATH_EQUAL_TO_HPP
#define SPROUT_MATH_EQUAL_TO_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/algorithm/max.hpp>
#include <sprout/math/abs.hpp>
#include <sprout/math/float_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			max3(T x, T y, T z) {
				return sprout::max(sprout::max(x, y), z);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			equal_to(FloatType x, FloatType y) {
				return x == y
					|| sprout::abs(x - y)
						<= std::numeric_limits<FloatType>::epsilon() * sprout::math::detail::max3(std::abs(x), std::abs(y), FloatType(1.0))
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			equal_to(IntType x, IntType y) {
				return x == y;
			}
		}	// namespace detail
		//
		// equal_to
		//
		template<
			typename T1,
			typename T2,
			typename sprout::enabler_if<std::is_arithmetic<T1>::value && std::is_arithmetic<T2>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		equal_to(T1 x, T2 y) {
			typedef typename sprout::math::float_promote<T1, T2>::type promoted;
			return sprout::math::detail::equal_to<promoted>(x, y);
		}
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_EQUAL_TO_HPP
