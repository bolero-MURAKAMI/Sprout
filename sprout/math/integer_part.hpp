#ifndef SPROUT_MATH_INTEGER_PART_HPP
#define SPROUT_MATH_INTEGER_PART_HPP

#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/trunc.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			integer_part(FloatType x) {
				return x == std::numeric_limits<FloatType>::infinity() ? std::numeric_limits<FloatType>::infinity()
					: x == -std::numeric_limits<FloatType>::infinity() ? -std::numeric_limits<FloatType>::infinity()
					: x == std::numeric_limits<FloatType>::quiet_NaN() ? std::numeric_limits<FloatType>::quiet_NaN()
					: sprout::trunc(x)
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			integer_part(IntType x) {
				return sprout::math::detail::integer_part(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::integer_part;
	}	// namespace math

	using sprout::math::integer_part;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_INTEGER_PART_HPP
