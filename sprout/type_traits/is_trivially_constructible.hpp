/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
#define SPROUT_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/detail/predef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/is_scalar.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	//
	// is_trivially_constructible
	//
#if !defined(_LIBCPP_VERSION)
#if SPROUT_CLANG_HAS_FUTURE(is_trivially_constructible)
	template<typename T, typename... Args>
	struct is_trivially_constructible
		: public sprout::bool_constant<__is_trivially_constructible(T, Args...)>
	{};
#else	// #if SPROUT_CLANG_HAS_FUTURE(is_trivially_constructible)
	template<typename T, typename... Args>
	struct is_trivially_constructible
		: public sprout::false_type
	{};
#if SPROUT_CLANG_HAS_FUTURE(has_trivial_constructor) || SPROUT_GCC_OR_LATER(4, 3, 0)
	template<typename T>
	struct is_trivially_constructible<T>
		: public sprout::bool_constant<__has_trivial_constructor(T)>
	{};
#else	// #if SPROUT_CLANG_HAS_FUTURE(has_trivial_constructor) || SPROUT_GCC_OR_LATER(4, 3, 0)
	template<typename T>
	struct is_trivially_constructible<T>
		: public sprout::is_scalar<T>
	{};
#endif	// #if SPROUT_CLANG_HAS_FUTURE(has_trivial_constructor) || SPROUT_GCC_OR_LATER(4, 3, 0)
	template<typename T>
	struct is_trivially_constructible<T, T&>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_constructible<T, T const&>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_constructible<T, T&&>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_constructible<T, T const&&>
		: public sprout::is_scalar<T>
	{};
#endif	// #if SPROUT_CLANG_HAS_FUTURE(is_trivially_constructible)
#else	// #if !defined(_LIBCPP_VERSION)
	template<typename T, typename... Args>
	struct is_trivially_constructible
		: public sprout::detail::type_traits_wrapper<std::is_trivially_constructible<T, Args...> >
	{};
#endif	// #if !defined(_LIBCPP_VERSION)

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T, typename... Args>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_constructible_v = sprout::is_trivially_constructible<T, Args...>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_TRIVIALLY_CONSTRUCTIBLE_HPP
