/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP
#define SPROUT_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/is_trivially_assignable.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	//
	// is_trivially_copy_assignable
	//
#if !defined(_LIBCPP_VERSION)
	template<typename T>
	struct is_trivially_copy_assignable
		: public sprout::is_trivially_assignable<
			typename std::add_lvalue_reference<T>::type,
			typename std::add_lvalue_reference<T>::type const
		>
	{};
#else	// #if !defined(_LIBCPP_VERSION)
	template<typename T>
	struct is_trivially_copy_assignable
		: public sprout::detail::type_traits_wrapper<std::is_trivially_copy_assignable<T> >
	{};
#endif	// #if !defined(_LIBCPP_VERSION)

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename T>
	SPROUT_STATIC_CONSTEXPR bool is_trivially_copy_assignable_v = sprout::is_trivially_copy_assignable<T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_IS_TRIVIALLY_COPY_ASSIGNABLE_HPP
