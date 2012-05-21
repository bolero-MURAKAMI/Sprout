#ifndef SPROUT_BREED_TAGS_HPP
#define SPROUT_BREED_TAGS_HPP

#include <sprout/config.hpp>
#include <sprout/breed/breed_fwd.hpp>

namespace sprout {
	namespace breed {
		namespace tagns_ {
			namespace tag {
				struct terminal {};
				struct unary_plus {};
				struct negate {};
				struct dereference {};
				struct complement {};
				struct address_of {};
				struct logical_not {};
				struct pre_inc {};
				struct pre_dec {};
				struct post_inc {};
				struct post_dec {};
				struct shift_left {};
				struct shift_right {};
				struct multiplies {};
				struct divides {};
				struct modulus {};
				struct plus {};
				struct minus {};
				struct less {};
				struct greater {};
				struct less_equal {};
				struct greater_equal {};
				struct equal_to {};
				struct not_equal_to {};
				struct logical_or {};
				struct logical_and {};
				struct bitwise_and {};
				struct bitwise_or {};
				struct bitwise_xor {};
				struct comma {};
				struct mem_ptr {};
				struct assign {};
				struct shift_left_assign {};
				struct shift_right_assign {};
				struct multiplies_assign {};
				struct divides_assign {};
				struct modulus_assign {};
				struct plus_assign {};
				struct minus_assign {};
				struct bitwise_and_assign {};
				struct bitwise_or_assign {};
				struct bitwise_xor_assign {};
				struct subscript {};
				struct member {};
				struct if_else_ {};
				struct function {};
			}	// namespace tag
		}	// namespace tagns_
	}	// namespace breed
}	// namespace sprout

#endif	// #ifndef SPROUT_BREED_TAGS_HPP
