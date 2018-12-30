/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_CONDITIONAL_HPP
#define SPROUT_TYPE_TRAITS_CONDITIONAL_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// conditional
	//
	using std::conditional;

#if SPROUT_USE_TEMPLATE_ALIASES
	template<bool B, typename T, typename F>
	using conditional_t = typename sprout::conditional<B, T, F>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_CONDITIONAL_HPP
