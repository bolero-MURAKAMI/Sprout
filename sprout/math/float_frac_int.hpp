#ifndef SPROUT_MATH_FLOAT_FRAC_INT_HPP
#define SPROUT_MATH_FLOAT_FRAC_INT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/float_integer_part.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/utility/pair/pair.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, T>
			float_frac_int_impl(T x, T ipart) {
				return sprout::pair<T, T>(x - ipart, ipart);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::pair<FloatType, FloatType>
			float_frac_int(FloatType x) {
				return sprout::math::detail::float_frac_int_impl(x, sprout::math::float_integer_part(x));
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::pair<double, double>
			float_frac_int(IntType x) {
				return sprout::math::detail::float_frac_int(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::float_frac_int;
	}	// namespace math

	using sprout::math::float_frac_int;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FLOAT_FRAC_INT_HPP
