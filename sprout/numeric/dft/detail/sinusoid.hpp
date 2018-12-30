/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_DFT_DETAIL_SINUSOID_HPP
#define SPROUT_NUMERIC_DFT_DETAIL_SINUSOID_HPP

#include <sprout/config.hpp>
#include <sprout/math/constants.hpp>
#include <sprout/math/sin.hpp>

namespace sprout {
	namespace detail {
		template<typename T, typename Index>
		inline SPROUT_CONSTEXPR T
		sinusoid_value(T const& amplitude, T const& phase, T const& d, Index i) {
			using sprout::sin;
			return amplitude * sin(d * T(i) + phase);
		}
		template<typename T, typename Size>
		inline SPROUT_CONSTEXPR T
		sinusoid_value_d(T const& frequency, Size size) {
			return sprout::math::two_pi<T>() * frequency / T(size);
		}
		template<typename T>
		inline SPROUT_CONSTEXPR T
		sinusoid_value_d(T const& frequency) {
			return sprout::math::two_pi<T>() * frequency;
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_DETAIL_SINUSOID_HPP
