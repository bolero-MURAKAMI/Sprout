/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
#define SPROUT_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/detail/predef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	//
	// is_trivially_destructible
	//
#if !defined(_LIBCPP_VERSION) && SPROUT_GCC_EARLIER(4, 8, 0)
#if SPROUT_CLANG_HAS_FUTURE(has_trivial_destructor) || SPROUT_GCC_OR_LATER(4, 3, 0)
	template<typename T>
	struct is_trivially_destructible
		: public sprout::bool_constant<sprout::is_destructible<T>::value && __has_trivial_destructor(T)>
	{};
#else	// #if SPROUT_CLANG_HAS_FUTURE(has_trivial_destructor) || SPROUT_GCC_OR_LATER(4, 3, 0)
	template<typename T>
	struct is_trivially_destructible
		: public sprout::bool_constant<
			sprout::is_destructible<T>::value
			&& (std::is_scalar<typename std::remove_all_extents<T>::type>::value
				|| std::is_reference<typename std::remove_all_extents<T>::type>::value
				)
		>
	{};
#endif	// #if SPROUT_CLANG_HAS_FUTURE(has_trivial_destructor) || SPROUT_GCC_OR_LATER(4, 3, 0)
#else	// #if !defined(_LIBCPP_VERSION) && SPROUT_GCC_EARLIER(4, 8, 0)
	template<typename T>
	struct is_trivially_destructible
		: public sprout::detail::type_traits_wrapper<std::is_trivially_destructible<T> >
	{};
#endif	// #if !defined(_LIBCPP_VERSION) && SPROUT_GCC_EARLIER(4, 8, 0)

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_destructible_v = sprout::is_trivially_destructible<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
