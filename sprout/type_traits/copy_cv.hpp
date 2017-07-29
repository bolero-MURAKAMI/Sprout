/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_COPY_CV_HPP
#define SPROUT_TYPE_TRAITS_COPY_CV_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	//
	// copy_cv
	//
	template<typename T, typename U>
	struct copy_cv
		: public sprout::identity<T>
	{};
	template<typename T, typename U>
	struct copy_cv<T, U const>
		: public std::add_const<T>
	{};
	template<typename T, typename U>
	struct copy_cv<T, U volatile>
		: public std::add_volatile<T>
	{};
	template<typename T, typename U>
	struct copy_cv<T, U const volatile>
		: public std::add_cv<T>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename U>
	using copy_cv_t = typename sprout::copy_cv<T, U>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_COPY_CV_HPP
