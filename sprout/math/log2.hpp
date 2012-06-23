#ifndef SPROUT_MATH_LOG2HPP
#define SPROUT_MATH_LOG2HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/log.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR FloatType
			log2(FloatType x) {
				return sprout::math::log(x) / sprout::math::ln_two<FloatType>();
			}

			template<
				typename IntType,
				typename sprout::enabler_if<std::is_integral<IntType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR double
			log2(IntType x) {
				return sprout::math::detail::log2(static_cast<double>(x));
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::log2;
	}	// namespace math

	using sprout::math::log2;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_LOG2HPP
