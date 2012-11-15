#ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_INHERIT_IF_TYPE_HPP
#define SPROUT_FUNCTIONAL_TYPE_TRAITS_INHERIT_IF_TYPE_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/inherit_if_xxx.hpp>

namespace sprout {
	//
	// inherit_if_result_type
	// inherit_if_argument_type
	// inherit_if_first_argument_type
	// inherit_if_second_argument_type
	//
	SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(result_type);
	SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(argument_type);
	SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(first_argument_type);
	SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(second_argument_type);
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_INHERIT_IF_TYPE_HPP
