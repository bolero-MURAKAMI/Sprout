/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TPP_ALGORITHM_ANY_OF_HPP
#define SPROUT_TPP_ALGORITHM_ANY_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<bool... Values>
			struct any_of_impl;
			template<>
			struct any_of_impl<>
				: public std::false_type
			{};
			template<>
			struct any_of_impl<true>
				: public std::true_type
			{};
			template<>
			struct any_of_impl<false>
				: public std::false_type
			{};
			template<bool... Tail>
			struct any_of_impl<true, Tail...>
				: public std::true_type
			{};
			template<bool... Tail>
			struct any_of_impl<false, Tail...>
				: public std::integral_constant<bool, sprout::tpp::detail::any_of_impl<Tail...>::value>
			{};
		}	// namespace detail
		//
		// any_of_c
		//
		template<bool... Values>
		struct any_of_c
			: public sprout::tpp::detail::any_of_impl<Values...>
		{};
		//
		// any_of
		//
		template<typename... Types>
		struct any_of
			: public sprout::tpp::any_of_c<Types::value...>
		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_ANY_OF_HPP
