/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TPP_ALGORITHM_NONE_OF_HPP
#define SPROUT_TPP_ALGORITHM_NONE_OF_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<bool... Values>
			struct none_of_impl;
			template<>
			struct none_of_impl<>
				: public sprout::true_type
			{};
			template<>
			struct none_of_impl<true>
				: public sprout::false_type
			{};
			template<>
			struct none_of_impl<false>
				: public sprout::true_type
			{};
			template<bool... Tail>
			struct none_of_impl<true, Tail...>
				: public sprout::false_type
			{};
			template<bool... Tail>
			struct none_of_impl<false, Tail...>
				: public sprout::integral_constant<bool, sprout::tpp::detail::none_of_impl<Tail...>::value>
			{};
		}	// namespace detail
		//
		// none_of_c
		//
		template<bool... Values>
		struct none_of_c
			: public sprout::tpp::detail::none_of_impl<Values...>
		{};
		//
		// none_of
		//
		template<typename... Types>
		struct none_of
			: public sprout::tpp::none_of_c<Types::value...>
		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_NONE_OF_HPP
