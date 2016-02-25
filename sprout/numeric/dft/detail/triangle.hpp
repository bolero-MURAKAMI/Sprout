/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_DFT_DETAIL_TRINAGLE_HPP
#define SPROUT_NUMERIC_DFT_DETAIL_TRINAGLE_HPP

#include <sprout/config.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/sin.hpp>
#include <sprout/math/asin.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR T
		triangle_value_impl(T const& t) {
			typedef double elem_type;
			using sprout::sin;
			using sprout::asin;
			return T(sprout::math::two_div_pi<elem_type>()) * asin(sin(T(sprout::math::two_pi<elem_type>()) * t));
		}
		template<typename T, typename Index>
		inline SPROUT_CONSTEXPR T
		triangle_value(T const& frequency, T const& amplitude, T const& phase, Index i) {
			return amplitude * sprout::detail::triangle_value_impl(frequency * T(i) + phase);
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_DETAIL_TRINAGLE_HPP
