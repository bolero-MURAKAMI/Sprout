#ifndef SPROUT_MATH_REM_QUO_HPP
#define SPROUT_MATH_REM_QUO_HPP

#include <limits>
#include <type_traits>
#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/signbit.hpp>
#include <sprout/math/quotient.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/type_traits/float_promote.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename R, typename FloatType, typename Pair>
			inline SPROUT_CONSTEXPR sprout::pair<FloatType, R>
			rem_quo_ret(Pair const& p) {
				typedef sprout::pair<FloatType, R> type;
				return type(static_cast<FloatType>(p.first), p.second);
			}

			template<typename R, typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, R>
			rem_quo_impl(T x, T y, R quo) {
				typedef sprout::pair<T, R> type;
				return type(x - quo * y, quo);
			}

			template<
				typename R = int,
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value && std::is_integral<R>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::pair<FloatType, R>
			rem_quo(FloatType x, FloatType y) {
				typedef sprout::pair<FloatType, R> type;
				return sprout::math::isnan(y)
						? sprout::math::isnan(x)
							? sprout::math::signbit(y) || sprout::math::signbit(x) ? type(-std::numeric_limits<FloatType>::quiet_NaN(), R(0))
								: type(std::numeric_limits<FloatType>::quiet_NaN(), R(0))
							: type(y, R(0))
					: x == 0 && y != 0 ? type(FloatType(0), R(0))
					: x == std::numeric_limits<FloatType>::infinity() || x == -std::numeric_limits<FloatType>::infinity() || y == 0
						? type(std::numeric_limits<FloatType>::quiet_NaN(), R(0))
					: y == std::numeric_limits<FloatType>::infinity() || y == -std::numeric_limits<FloatType>::infinity() ? type(x, R(0))
					: sprout::math::detail::rem_quo_ret<R, FloatType>(sprout::math::detail::rem_quo_impl(
						static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x),
						static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(y),
						sprout::math::quotient<R>(x, y)
						))
					;
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
