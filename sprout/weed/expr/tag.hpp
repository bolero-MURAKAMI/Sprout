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
		}	// namespace tag
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_EXPR_TAG_HPP
