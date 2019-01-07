/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_FFT_IFFT_HPP
#define SPROUT_RANGE_NUMERIC_FFT_IFFT_HPP

#include <sprout/config.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/numeric/fft/ifft.hpp>

namespace sprout {
	namespace range {
		//
		// ifft
		//
		template<typename RandomAccessRange>
		inline SPROUT_CXX14_CONSTEXPR void
		ifft(RandomAccessRange&& rng) {
			sprout::ifft(sprout::begin(SPROUT_FORWARD(RandomAccessRange, rng)), sprout::end(SPROUT_FORWARD(RandomAccessRange, rng)));
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_FFT_IFFT_HPP
