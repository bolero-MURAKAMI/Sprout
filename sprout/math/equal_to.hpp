#ifndef SPROUT_MATH_EQUAL_TO_HPP
#define SPROUT_MATH_EQUAL_TO_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/algorithm/max.hpp>
#include <sprout/math/fabs.hpp>
#include <sprout/type_traits/arithmetic_promote.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			max3(T x, T y, T z) {
				return sprout::max(sprout::max(x, y), z);
			}

			template<typename FloatType>
			inline SPROUT_CONSTEXPR bool
			equal_to_impl(FloatType x, FloatType y) {
				return x == y
					|| sprout::fabs(x - y)
						<= std::numeric_limits<FloatType>::epsilon() * sprout::math::detail::max3(sprout::fabs(x), sprout::fabs(y), FloatType(1))
					;
			}

			template<
				typename FloatType1, typename FloatType2,
				typename sprout::enabler_if<
					std::is_floating_point<typename sprout::arithmetic_promote<FloatType1, FloatType2>::type>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			equal_to(FloatType1 x, FloatType2 y) {
				typedef typename sprout::arithmetic_promote<FloatType1, FloatType2>::type type;
				return sprout::math::detail::equal_to_impl<type>(x, y);
			}

			template<
				typename IntType1, typename IntType2,
				typename sprout::enabler_if<
					std::is_integral<typename sprout::arithmetic_promote<IntType1, IntType2>::type>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			equal_to(IntType1 x, IntType2 y) {
				return x == y;
			}
		}	// namespace detail
		//
		// equal_to
		//
		template<
			typename T, typename U,
			typename sprout::enabler_if<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		equal_to(T x, U y) {
			return sprout::math::detail::equal_to(x, y);
		}
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_EQUAL_TO_HPP
