/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_NUMERIC_DFT_DETAIL_SQUARE_HPP
#define SPROUT_NUMERIC_DFT_DETAIL_SQUARE_HPP

#include <sprout/config.hpp>
#include <sprout/numeric/dft/detail/sawtooth.hpp>

namespace sprout {
	namespace detail {
		template<typename T>
		inline SPROUT_CONSTEXPR T
		square_value_impl(T const& t, T const& duty) {
			return sprout::detail::sawtooth_value_impl(t) - sprout::detail::sawtooth_value_impl(t - duty);
		}
		template<typename T, typename Index>
		inline SPROUT_CONSTEXPR T
		square_value(T const& frequency, T const& amplitude, T const& phase, T const& duty, Index i) {
			return amplitude * sprout::detail::square_value_impl(frequency * T(i) + phase, duty);
		}
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_NUMERIC_DFT_DETAIL_SQUARE_HPP
