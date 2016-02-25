/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_DFT_DETAIL_SAWTOOTH_HPP
#define SPROUT_NUMERIC_DFT_DETAIL_SAWTOOTH_HPP

#include <sprout/config.hpp>
#include <sprout/math/floor.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR T
		sawtooth_value_impl(T const& t) {
			using sprout::floor;
			return 2 * (t - floor(t + T(0.5)));
		}
		template<typename T, typename Index>
		inline SPROUT_CONSTEXPR T
		sawtooth_value(T const& frequency, T const& amplitude, T const& phase, Index i) {
			return amplitude * sprout::detail::sawtooth_value_impl(frequency * T(i) + phase);
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_DETAIL_SAWTOOTH_HPP
