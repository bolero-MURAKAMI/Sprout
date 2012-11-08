#ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_HPP
#define SPROUT_FUNCTIONAL_TYPE_TRAITS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/has_xxx.hpp>
#include <sprout/type_traits/inherit_if_xxx.hpp>

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

	//
	// inhert_if_result_type
	// inhert_if_argument_type
	// inhert_if_first_argument_type
	// inhert_if_second_argument_type
	//
	SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(result_type);
	SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(argument_type);
	SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(first_argument_type);
	SPROUT_INHERIT_IF_XXX_TYPE_DEF_LAZY(second_argument_type);

	//
	// is_strict_unary_function
	//
	template<typename Fn>
	struct is_strict_unary_function
		: public std::integral_constant<
			bool,
			sprout::has_result_type<Fn>::value
				&& sprout::has_argument_type<Fn>::value
		>
	{};
	//
	// is_strict_binary_function
	//
	template<typename Fn>
	struct is_strict_binary_function
		: public std::integral_constant<
			bool,
			sprout::has_result_type<Fn>::value
				&& sprout::has_first_argument_type<Fn>::value
				&& sprout::has_second_argument_type<Fn>::value
		>
	{};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_HPP
