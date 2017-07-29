/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_QUOTE_HPP
#define SPROUT_TYPE_QUOTE_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace types {
		//
		// quote
		//
		template<template<typename...> class F>
		struct quote {
		public:
#if SPROUT_USE_TEMPLATE_ALIASES
			template<typename... Types>
			using apply = F<Types...>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
			template<typename... Types>
			struct apply
				: public F<Types...>
			{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
		};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_QUOTE_HPP
