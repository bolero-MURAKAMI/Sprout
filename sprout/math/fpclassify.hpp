#ifndef SPROUT_MATH_FPCLASSIFY_HPP
#define SPROUT_MATH_FPCLASSIFY_HPP

#include <cmath>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/detail/config.hpp>
#include <sprout/math/isnan.hpp>
#include <sprout/math/isinf.hpp>
#include <sprout/math/iszero.hpp>
#include <sprout/math/issubnormal.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR int
			fpclassify(FloatType x) {
				return sprout::math::isnan(x) ? FP_NAN
					: sprout::math::isinf(x) ? FP_INFINITE
					: sprout::math::iszero(x) ? FP_ZERO
					: sprout::math::detail::issubnormal_or_zero(x) ? FP_SUBNORMAL
					: FP_NORMAL
					;
			}
		}	// namespace detail

		using NS_SPROUT_MATH_DETAIL::fpclassify;
	}	// namespace math

	using sprout::math::fpclassify;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_FPCLASSIFY_HPP
