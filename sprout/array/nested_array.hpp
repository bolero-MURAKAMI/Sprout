/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ARRAY_NESTED_ARRAY_HPP
#define SPROUT_ARRAY_NESTED_ARRAY_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/array/array.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace detail {
		template<typename T, std::size_t... Ns>
		struct nested_array_t_impl;
		template<typename T, std::size_t N>
		struct nested_array_t_impl<T, N>
			: public sprout::identity<sprout::array<T, N> >
		{};
		template<typename T, std::size_t N, std::size_t... Ms>
		struct nested_array_t_impl<T, N, Ms...>
			: public sprout::detail::nested_array_t_impl<sprout::array<T, N>, Ms...>
		{};
	}	// namespace detail
	//
	// nested_array_t
	//
	template<typename T, std::size_t... Ns>
	struct nested_array_t
		: public sprout::detail::nested_array_t_impl<T, Ns...>
	{};

#if SPROUT_USE_TEMPLATE_ALIASES
	//
	// nested_array
	//
	template<typename T, std::size_t... Ns>
	using nested_array = typename sprout::nested_array_t<T, Ns...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_ARRAY_NESTED_ARRAY_HPP
