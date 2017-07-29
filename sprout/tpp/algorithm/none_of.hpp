/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TPP_ALGORITHM_NONE_OF_HPP
#define SPROUT_TPP_ALGORITHM_NONE_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type/type_tuple.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<typename Tup, std::size_t First, std::size_t Last, bool = (Last - First == 1)>
			struct none_of_impl
				: public sprout::bool_constant<!std::tuple_element<First, Tup>::type::value>
			{};
			template<typename Tup, std::size_t First, std::size_t Last>
			struct none_of_impl<Tup, First, Last, false>
				: public sprout::bool_constant<
					sprout::tpp::detail::none_of_impl<Tup, First, (First + Last) / 2>::value
						&& sprout::tpp::detail::none_of_impl<Tup, (First + Last) / 2, Last>::value
				>
			{};
		}	// namespace detail
		//
		// none_of
		//
		template<typename... Types>
		struct none_of
			: public sprout::tpp::detail::none_of_impl<sprout::types::type_tuple<Types...>, 0, sizeof...(Types)>
		{};
		template<>
		struct none_of<>
			: public sprout::true_type
		{};
		//
		// none_of_c
		//
		template<bool... Values>
		struct none_of_c
			: public sprout::tpp::none_of<sprout::bool_constant<Values>...>
		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_NONE_OF_HPP
