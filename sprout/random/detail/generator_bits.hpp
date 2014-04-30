/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_DETAIL_GENERATOR_BITS_HPP
#define SPROUT_RANDOM_DETAIL_GENERATOR_BITS_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/limits.hpp>

namespace sprout {
	namespace random {
		namespace detail {
			template<typename URNG>
			struct generator_bits {
			public:
				static SPROUT_CONSTEXPR std::size_t value() {
					return sprout::numeric_limits<typename URNG::result_type>::digits;
				}
			};
		}	// namespace detail
	}	// namespace random
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_DETAIL_GENERATOR_BITS_HPP
