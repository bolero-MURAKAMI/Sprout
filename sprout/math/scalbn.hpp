#ifndef SPROUT_MATH_SCALBN_HPP
#define SPROUT_MATH_SCALBN_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/detail/pow.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/detail/float_compute.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename FloatType, typename T>
			inline SPROUT_CONSTEXPR T
			scalbn_impl(T x, int exp) {
				return x * sprout::detail::pow_n(T(sprout::numeric_limits<FloatType>::radix), exp);
			}

			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			scalbn(FloatType x, int exp) {
				return sprout::math::isnan(x) ? x
					: x == sprout::numeric_limits<FloatType>::infinity() ? sprout::numeric_limits<FloatType>::infinity()
					: x == -sprout::numeric_limits<FloatType>::infinity() ? -sprout::numeric_limits<FloatType>::infinity()
					: exp == 0 ? x
					: x == 0 ? x
					: static_cast<FloatType>(sprout::math::detail::scalbn_impl<FloatType>(static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x), exp))
					;
			}
			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			scalbn(IntType x, int exp) {
				return sprout::math::detail::scalbn(static_cast<double>(x), exp);
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::scalbn;
	}	// namespace math

	using sprout::math::scalbn;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_SCALBN_HPP
