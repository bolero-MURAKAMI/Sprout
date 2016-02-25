/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_EXPR_TAG_HPP
#define SPROUT_WEED_EXPR_TAG_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace weed {
		namespace tag {
			struct terminal {};
			struct unary_plus {};
			struct negate {};
			struct dereference {};
			struct address_of {};
			struct logical_not {};
			struct shift_left {};
			struct modulus {};
			struct minus {};
			struct bitwise_or {};
			struct mem_ptr {};
		}	// namespace tag
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_EXPR_TAG_HPP
