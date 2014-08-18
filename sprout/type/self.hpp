/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_SELF_HPP
#define SPROUT_TYPE_SELF_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace types {
		//
		// self
		//
		template<template<typename...> class F>
		struct self {
		public:
#if SPROUT_USE_TEMPLATE_ALIASES
			template<typename... Types>
			using apply = sprout::identity<F<Types...> >;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
			template<typename... Types>
			struct apply
				: public sprout::identity<F<Types...> >
			{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
		};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_SELF_HPP
