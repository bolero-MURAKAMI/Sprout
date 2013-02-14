#ifndef SPROUT_MATH_FRAC_INT_HPP
#define SPROUT_MATH_FRAC_INT_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/integer_part.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, T>
			frac_int_impl(T x, T ipart) {
				typedef sprout::pair<T, T> type;
				return  x == std::numeric_limits<T>::infinity() || x == -std::numeric_limits<T>::infinity() ? type(T(0), ipart)
					: x == std::numeric_limits<T>::quiet_NaN() ? type(std::numeric_limits<T>::quiet_NaN(), ipart)
					: type(x - ipart, ipart)
					;
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::pair<FloatType, FloatType>
			frac_int(FloatType x) {
				return sprout::math::detail::frac_int_impl(x, sprout::math::integer_part(x));
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::pair<double, double>
			frac_int(IntType x) {
				return sprout::math::detail::frac_int(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::frac_int;
	}	// namespace math

	using sprout::math::frac_int;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FRAC_INT_HPP
