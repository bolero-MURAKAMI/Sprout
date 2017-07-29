/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_IS_STRICT_FUNCTION_HPP
#define SPROUT_FUNCTIONAL_TYPE_TRAITS_IS_STRICT_FUNCTION_HPP

#include <sprout/config.hpp>
#include <sprout/functional/type_traits/has_type.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	//
	// is_strict_unary_function
	// is_strict_binary_function
	//
	template<typename Fn>
	struct is_strict_unary_function
		: public sprout::bool_constant<
			sprout::has_result_type<Fn>::value
				&& sprout::has_argument_type<Fn>::value
		>
	{};
	template<typename Fn>
	struct is_strict_binary_function
		: public sprout::bool_constant<
			sprout::has_result_type<Fn>::value
				&& sprout::has_first_argument_type<Fn>::value
				&& sprout::has_second_argument_type<Fn>::value
		>
	{};
	//
	// is_strict_function
	//
	template<typename Fn>
	struct is_strict_function
		: public sprout::bool_constant<
			sprout::is_strict_unary_function<Fn>::value
				|| sprout::is_strict_binary_function<Fn>::value
		>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_strict_unary_function_v = sprout::is_strict_unary_function<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_strict_binary_function_v = sprout::is_strict_binary_function<T>::value;
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_strict_function_v = sprout::is_strict_function<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_TYPE_TRAITS_IS_STRICT_FUNCTION_HPP
