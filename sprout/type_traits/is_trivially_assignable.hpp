/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP
#define SPROUT_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/detail/predef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/is_scalar.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	//
	// is_trivially_assignable
	//
#if !defined(_LIBCPP_VERSION)
#if SPROUT_CLANG_HAS_FUTURE(is_trivially_assignable)
	template<typename T, typename U>
	struct is_trivially_assignable
		: public sprout::bool_constant<__is_trivially_assignable(T, U)>
	{};
#else	// #if SPROUT_CLANG_HAS_FUTURE(is_trivially_assignable)
	template<typename T, typename U>
	struct is_trivially_assignable
		: public sprout::false_type
	{};
	template<typename T>
	struct is_trivially_assignable<T&, T>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_assignable<T&, T&>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_assignable<T&, T const&>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_assignable<T&, T&&>
		: public sprout::is_scalar<T>
	{};
	template<typename T>
	struct is_trivially_assignable<T&, T const&&>
		: public sprout::is_scalar<T>
	{};
#endif	// #if SPROUT_CLANG_HAS_FUTURE(is_trivially_assignable)
#else	// #if !defined(_LIBCPP_VERSION)
	template<typename T, typename U>
	struct is_trivially_assignable
		: public sprout::detail::type_traits_wrapper<std::is_trivially_assignable<T, U> >
	{};
#endif	// #if !defined(_LIBCPP_VERSION)

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T, typename U>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_assignable_v = sprout::is_trivially_assignable<T, U>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_TRIVIALLY_ASSIGNABLE_HPP
