#ifndef SPROUT_MATH_FLOAT_PAIR_HPP
#define SPROUT_MATH_FLOAT_PAIR_HPP

#include <cfloat>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/float_exponent.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/utility/pair.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename T>
			inline SPROUT_CONSTEXPR sprout::pair<T, int>
			float_pair_impl(T x, int exp) {
				return sprout::pair<T, int>(x / sprout::detail::pow_n(T(FLT_RADIX), exp), exp);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::pair<FloatType, int>
			float_pair(FloatType x) {
				return sprout::math::detail::float_pair_impl(x, sprout::math::float_exponent(x));
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR sprout::pair<double, int>
			float_pair(IntType x) {
				return sprout::math::detail::float_pair(static_cast<double>(x));
			}
		}	// namespace detail

		using sprout::math::detail::float_pair;
	}	// namespace math

	using sprout::math::float_pair;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FLOAT_PAIR_HPP
