/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANGE_NUMERIC_DFT_IDFT_ELEMENT_HPP
#define SPROUT_RANGE_NUMERIC_DFT_IDFT_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/container/functions.hpp>
#include <sprout/numeric/dft/idft_element.hpp>

namespace sprout {
	namespace range {
		//
		// idft_element
		//
		template<typename InputRange>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<InputRange>::value_type
		idft_element(InputRange const& input, typename sprout::container_traits<InputRange>::difference_type i) {
			return sprout::idft_element(sprout::begin(input), sprout::end(input), i);
		}
	}	// namespace range
}	// namespace sprout

#endif	// #ifndef SPROUT_RANGE_NUMERIC_DFT_IDFT_ELEMENT_HPP
