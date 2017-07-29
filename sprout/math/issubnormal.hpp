/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ISSUBNORMAL_HPP
#define SPROUT_MATH_ISSUBNORMAL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/limits.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/math/iszero.hpp>
#include <sprout/math/isnan.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			//
			// issubnormal_or_zero
			//
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			issubnormal_or_zero(FloatType x) {
				return x > 0
					? x < sprout::numeric_limits<double>::min()
					: x > -sprout::numeric_limits<double>::min()
					;
			}
		}	// namespace detail
		//
		// issubnormal
		//
		template<
			typename FloatType,
			typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
		>
		inline SPROUT_CONSTEXPR bool
		issubnormal(FloatType x) {
			return !sprout::math::isnan(x)
				&& !sprout::math::iszero(x)
				&& sprout::math::detail::issubnormal_or_zero(x)
				;
		}
	}	// namespace math

	using sprout::math::issubnormal;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ISSUBNORMAL_HPP
