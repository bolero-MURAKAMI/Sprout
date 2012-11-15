#ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_HAS_TYPE_HPP
#define SPROUT_FUNCTIONAL_TYPE_TRAITS_HAS_TYPE_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/has_xxx.hpp>

namespace sprout {
	//
	// has_result_type
	// has_argument_type
	// has_first_argument_type
	// has_second_argument_type
	//
	SPROUT_HAS_XXX_TYPE_DEF_LAZY(result_type);
	SPROUT_HAS_XXX_TYPE_DEF_LAZY(argument_type);
	SPROUT_HAS_XXX_TYPE_DEF_LAZY(first_argument_type);
	SPROUT_HAS_XXX_TYPE_DEF_LAZY(second_argument_type);
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_HAS_TYPE_HPP
