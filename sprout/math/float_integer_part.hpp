#ifndef SPROUT_MATH_FLOAT_INTEGER_PART_HPP
#define SPROUT_MATH_FLOAT_INTEGER_PART_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/floor.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			float_integer_part(FloatType x) {
				return sprout::math::floor(x);
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			float_integer_part(IntType x) {
				return sprout::math::detail::float_integer_part(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::float_integer_part;
	}	// namespace math

	using sprout::math::float_integer_part;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FLOAT_INTEGER_PART_HPP
