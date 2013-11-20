/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_CV_HPP
#define SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_CV_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/std_type_traits.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	//
	// remove_shallow_cv
	//
	template<typename T>
	struct remove_shallow_cv
		: public sprout::identity<T>
	{};
	template<typename T>
	struct remove_shallow_cv<T const>
		: public sprout::conditional<sprout::is_array<T>::value, T const, T>
	{};
	template<typename T>
	struct remove_shallow_cv<T volatile>
		: public sprout::conditional<sprout::is_array<T>::value, T volatile, T>
	{};
	template<typename T>
	struct remove_shallow_cv<T const volatile>
		: public sprout::conditional<sprout::is_array<T>::value, T const volatile, T>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T>
	using remove_shallow_cv_t = typename sprout::remove_shallow_cv<T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_REMOVE_SHALLOW_CV_HPP
