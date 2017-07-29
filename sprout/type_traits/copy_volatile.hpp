/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_COPY_VOLATILE_HPP
#define SPROUT_TYPE_TRAITS_COPY_VOLATILE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	//
	// copy_volatile
	//
	template<typename T, typename U>
	struct copy_volatile
		: public sprout::identity<T>
	{};
	template<typename T, typename U>
	struct copy_volatile<T, U volatile>
		: public std::add_volatile<T>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<typename T, typename U>
	using copy_volatile_t = typename sprout::copy_volatile<T, U>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_COPY_VOLATILE_HPP
