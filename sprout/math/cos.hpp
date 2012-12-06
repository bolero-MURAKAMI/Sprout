#ifndef SPROUT_MATH_COS_HPP
#define SPROUT_MATH_COS_HPP

#include <cstddef>
#include <limits>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/factorial.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/fmod.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR T
			cos_impl_1(T x2, std::size_t first, std::size_t last) {
				return last - first == 1
					? (first % 2 ? -1 : 1) * sprout::detail::pow_n(x2, first) / sprout::math::factorial<T>(2 * first)
					: sprout::math::detail::cos_impl_1(x2, first, first + (last - first) / 2)
						+ sprout::math::detail::cos_impl_1(x2, first + (last - first) / 2, last)
					;
			}
			template<typename FloatType>
			inline SPROUT_CONSTEXPR FloatType
			cos_impl(FloatType x) {
				typedef double type;
				return static_cast<FloatType>(
					type(1) + sprout::math::detail::cos_impl_1(
						static_cast<type>(x) * static_cast<type>(x),
						1, sprout::math::factorial_limit<type>() / 2 + 1
						)
					);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			cos(FloatType x) {
				typedef double type;
				return x == std::numeric_limits<FloatType>::infinity()
					|| x == -std::numeric_limits<FloatType>::infinity()
					? std::numeric_limits<FloatType>::quiet_NaN()
					: sprout::math::detail::cos_impl(sprout::math::fmod(x, 2 * sprout::math::pi<FloatType>()))
					;
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			cos(IntType x) {
				return sprout::math::detail::cos(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::cos;
	}	// namespace math

	using sprout::math::cos;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_COS_HPP
