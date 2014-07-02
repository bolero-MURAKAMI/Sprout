/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_ENABLE_IF_HPP
#define SPROUT_TYPE_TRAITS_ENABLE_IF_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/std_type_traits.hpp>
#include <sprout/type_traits/std_type_aliases.hpp>

namespace sprout {
	//
	// disable_if
	//
	template<bool B, typename T = void>
	struct disable_if
		: public sprout::enable_if<!B, T>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	template<bool B, typename T = void>
	using disable_if_t = typename sprout::disable_if<B, T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_ENABLE_IF_HPP
