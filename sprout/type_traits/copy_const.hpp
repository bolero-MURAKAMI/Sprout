/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_COPY_CONST_HPP
#define SPROUT_TYPE_TRAITS_COPY_CONST_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	//
	// copy_const
	//
	template<typename T, typename U>
	struct copy_const
		: public sprout::identity<T>
	{};
	template<typename T, typename U>
	struct copy_const<T, U volatile>
		: public std::add_const<T>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename U>
	using copy_const_t = typename sprout::copy_const<T, U>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_COPY_CONST_HPP
