/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MATH_DETAIL_FLOAT_COMPUTE_HPP
#define SPROUT_MATH_DETAIL_FLOAT_COMPUTE_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/float_promote.hpp>

namespace sprout {
	namespace math {
		namespace detail {
			template<typename... Types>
			struct float_compute
				: public sprout::float_promote<double, Types...>
			{};

			template<typename FloatType>
			inline SPROUT_CONSTEXPR typename sprout::math::detail::float_compute<FloatType>::type
			as_float_compute(FloatType const& x) {
				return static_cast<typename sprout::math::detail::float_compute<FloatType>::type>(x);
			}
		}	// namespace detail
	}	// namespace math
}	// namespace sprout

#endif	// #ifndef SPROUT_MATH_DETAIL_FLOAT_COMPUTE_HPP
