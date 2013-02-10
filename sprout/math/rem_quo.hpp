#ifndef SPROUT_MATH_REM_QUO_HPP
#define SPROUT_MATH_REM_QUO_HPP

#include <cstdint>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/quotient.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename R, typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, R>
			rem_quo_impl(T x, T y, R quo) {
				return sprout::pair<T, T>(x - quo * y, quo);
			}
			template<
				typename R = int,
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<R>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::pair<FloatType, R>
			rem_quo(FloatType x, FloatType y) {
				return sprout::math::detail::rem_quo_impl(x, y, sprout::math::quotient(x, y));
			}

			template<
				typename R = int,
				typename ArithmeticType1,
				typename ArithmeticType2,
				typename sprout::enabler_if<
					std::is_arithmetic<ArithmeticType1>::value && std::is_arithmetic<ArithmeticType2>::value && std::is_integral<R>::value
				>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::pair<
				typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type,
				R
			>
			rem_quo(ArithmeticType1 x, ArithmeticType2 y) {
				typedef typename sprout::float_promote<ArithmeticType1, ArithmeticType2>::type type;
				return sprout::math::detail::rem_quo(static_cast<type>(x), static_cast<type>(y));
			}
		}	// namespace detail

		using sprout::math::detail::rem_quo;
	}	// namespace math

	using sprout::math::rem_quo;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_REM_QUO_HPP
