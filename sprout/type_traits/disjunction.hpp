/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_DISJUNCTION_HPP
#define SPROUT_TYPE_TRAITS_DISJUNCTION_HPP

#include <sprout/config.hpp>
#include <sprout/tpp/algorithm/any_of.hpp>

namespace sprout {
	//
	// disjunction
	//
	template<typename... Types>
	struct disjunction
		: public sprout::tpp::any_of<Types...>
	{};

#if SPROUT_USE_VARIABLE_TEMPLATES
	template<typename... Types>
	SPROUT_STATIC_CONSTEXPR bool disjunction_v = sprout::disjunction<Types...>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_DISJUNCTION_HPP
