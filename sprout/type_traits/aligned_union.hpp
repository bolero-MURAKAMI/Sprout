/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TRAITS_ALIGNED_UNION_HPP
#define SPROUT_TYPE_TRAITS_ALIGNED_UNION_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/alignment_of.hpp>
#if !defined(_LIBCPP_VERSION) || (_LIBCPP_VERSION < 1101)
#	include <sprout/tpp/algorithm/max_element.hpp>
#endif

namespace sprout {
	//
	// aligned_union
	//
#if !defined(_LIBCPP_VERSION) || (_LIBCPP_VERSION < 1101)
	template<std::size_t Len, typename... Types>
	struct aligned_union
		: public std::aligned_storage<
			sprout::tpp::max_element_c<std::size_t, Len, sizeof(Types)...>::value,
			sprout::tpp::max_element_c<std::size_t, sprout::alignment_of<Types>::value...>::value
		>
	{};
#else	// #if !defined(_LIBCPP_VERSION) || (_LIBCPP_VERSION < 1101)
	using std::aligned_union;
#endif	// #if !defined(_LIBCPP_VERSION) || (_LIBCPP_VERSION < 1101)

#if SPROUT_USE_TEMPLATE_ALIASES
	template<std::size_t Len, typename... Types>
	using aligned_union_t = typename sprout::aligned_union<Len, Types...>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TRAITS_ALIGNED_UNION_HPP
