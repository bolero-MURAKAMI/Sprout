#ifndef SPROUT_MATH_FRACTIONAL_PART_HPP
#define SPROUT_MATH_FRACTIONAL_PART_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/integer_part.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			fractional_part(FloatType x) {
				return x - sprout::math::integer_part(x);
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			fractional_part(IntType x) {
				return sprout::math::detail::fractional_part(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::fractional_part;
	}	// namespace math

	using sprout::math::fractional_part;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FRACTIONAL_PART_HPP
