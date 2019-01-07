/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TPP_ALGORITHM_ANY_OF_HPP
#define SPROUT_TPP_ALGORITHM_ANY_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type/type_tuple.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<typename Tup, std::size_t First, std::size_t Last, bool = (Last - First == 1)>
			struct any_of_impl
				: public std::tuple_element<First, Tup>::type
			{};
			template<typename Tup, std::size_t First, std::size_t Last>
			struct any_of_impl<Tup, First, Last, false>
				: public sprout::bool_constant<
					sprout::tpp::detail::any_of_impl<Tup, First, (First + Last) / 2>::value
						|| sprout::tpp::detail::any_of_impl<Tup, (First + Last) / 2, Last>::value
				>
			{};
		}	// namespace detail
		//
		// any_of
		//
		template<typename... Types>
		struct any_of
			: public sprout::tpp::detail::any_of_impl<sprout::types::type_tuple<Types...>, 0, sizeof...(Types)>
		{};
		template<>
		struct any_of<>
			: public sprout::false_type
		{};
		//
		// any_of_c
		//
		template<bool... Values>
		struct any_of_c
			: public sprout::tpp::any_of<sprout::bool_constant<Values>...>
		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_ANY_OF_HPP
