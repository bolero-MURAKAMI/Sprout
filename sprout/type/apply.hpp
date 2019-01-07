/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_APPLY_HPP
#define SPROUT_TYPE_APPLY_HPP

#include <sprout/config.hpp>
#include <sprout/type/quote.hpp>

namespace sprout {
	namespace types {
		//
		// apply
		//
#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename F, typename... Types>
		using apply = typename F::template apply<Types...>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
		template<typename F, typename... Types>
		struct apply
			: public F::template apply<Types...>
		{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename F, typename... Types>
		using apply_t = typename sprout::types::apply<F, Types...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename F, typename... Types>
		SPROUT_STATIC_CONSTEXPR decltype(sprout::types::apply<F, Types...>::value) apply_v = sprout::types::apply<F, Types...>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES

		//
		// apply_q
		//
#if SPROUT_USE_TEMPLATE_ALIASES
		template<template<typename...> class F, typename... Types>
		using apply_q = sprout::types::apply<sprout::types::quote<F>, Types...>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
		template<template<typename...> class F, typename... Types>
		struct apply_q
			: public sprout::types::apply<sprout::types::quote<F>, Types...>
		{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_TEMPLATE_ALIASES
		template<template<typename...> class F, typename... Types>
		using apply_q_t = typename sprout::types::apply_q<F, Types...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<template<typename...> class F, typename... Types>
		SPROUT_STATIC_CONSTEXPR decltype(sprout::types::apply_q<F, Types...>::value) apply_q_v = sprout::types::apply_q<F, Types...>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_APPLY_HPP
