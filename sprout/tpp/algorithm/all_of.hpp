/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TPP_ALGORITHM_ALL_OF_HPP
#define SPROUT_TPP_ALGORITHM_ALL_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<bool... Values>
			struct all_of_impl;
			template<>
			struct all_of_impl<>
				: public sprout::true_type
			{};
			template<>
			struct all_of_impl<true>
				: public sprout::true_type
			{};
			template<>
			struct all_of_impl<false>
				: public sprout::false_type
			{};
			template<bool... Tail>
			struct all_of_impl<true, Tail...>
				: public sprout::integral_constant<bool, sprout::tpp::detail::all_of_impl<Tail...>::value>
			{};
			template<bool... Tail>
			struct all_of_impl<false, Tail...>
				: public sprout::false_type
			{};
		}	// namespace detail
		//
		// all_of_c
		//
		template<bool... Values>
		struct all_of_c
			: public sprout::tpp::detail::all_of_impl<Values...>
		{};
		//
		// all_of
		//
		template<typename... Types>
		struct all_of
			: public sprout::tpp::all_of_c<Types::value...>
		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_ALL_OF_HPP
