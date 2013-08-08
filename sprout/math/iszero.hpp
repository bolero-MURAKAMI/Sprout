/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_ISZERO_HPP
#define SPROUT_MATH_ISZERO_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/enabler_if.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<
				typename FloatType,
				typename sprout::enabler_if<std::is_floating_point<FloatType>::value>::type = sprout::enabler
			>
			inline SPROUT_CONSTEXPR bool
			iszero(FloatType x) {
				return x == 0;
			}
		}	// namespace detail

		using sprout::math::detail::iszero;
	}	// namespace math

	using sprout::math::iszero;
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_ISZERO_HPP
