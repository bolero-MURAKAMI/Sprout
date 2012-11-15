#ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_IS_STRICT_FUNCTION_HPP
#define SPROUT_FUNCTIONAL_TYPE_TRAITS_IS_STRICT_FUNCTION_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/functional/type_traits/has_type.hpp>

namespace sprout {
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

#endif	// #ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_IS_STRICT_FUNCTION_HPP
