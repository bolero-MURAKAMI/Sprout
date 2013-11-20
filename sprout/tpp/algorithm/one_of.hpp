/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TPP_ALGORITHM_ONE_OF_HPP
#define SPROUT_TPP_ALGORITHM_ONE_OF_HPP

#include <sprout/config.hpp>
#include <sprout/tpp/algorithm/none_of.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<bool... Values>
			struct one_of_impl;
			template<>
			struct one_of_impl<>
				: public sprout::false_type
			{};
			template<>
			struct one_of_impl<true>
				: public sprout::true_type
			{};
			template<>
			struct one_of_impl<false>
				: public sprout::false_type
			{};
			template<bool... Tail>
			struct one_of_impl<true, Tail...>
				: public sprout::tpp::none_of_c<Tail...>
			{};
			template<bool... Tail>
			struct one_of_impl<false, Tail...>
				: public sprout::integral_constant<bool, sprout::tpp::detail::one_of_impl<Tail...>::value>
			{};
		}	// namespace detail
		//
		// one_of_c
		//
		template<bool... Values>
		struct one_of_c
			: public sprout::tpp::detail::one_of_impl<Values...>
		{};
		//
		// one_of
		//
		template<typename... Types>
		struct one_of
			: public sprout::tpp::one_of_c<Types::value...>
		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_ONE_OF_HPP
