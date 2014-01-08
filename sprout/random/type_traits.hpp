/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_RANDOM_TYPE_TRAITS_HPP
#define SPROUT_RANDOM_TYPE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/has_xxx.hpp>

namespace sprout {
	namespace random {
		//
		// is_seed_seq
		//
		SPROUT_HAS_XXX_TYPE_DEF(is_seed_seq, result_type);
	}	// namespace random
}	// namespace sprout

#endif	// #ifndef SPROUT_RANDOM_TYPE_TRAITS_HPP
