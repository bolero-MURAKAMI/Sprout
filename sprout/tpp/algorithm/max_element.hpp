/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TPP_ALGORITHM_MAX_ELEMENT_HPP
#define SPROUT_TPP_ALGORITHM_MAX_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/common_decay.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<typename T, T... Values>
			struct max_element_impl;
			template<typename T, T Value>
			struct max_element_impl<T, Value>
				: public sprout::integral_constant<T, Value>
			{};
			template<typename T, T Value1, T Value2>
			struct max_element_impl<T, Value1, Value2>
				: public sprout::integral_constant<T, (Value1 < Value2 ? Value2 : Value1)>
			{};
			template<typename T, T Value1, T Value2, T... Tail>
			struct max_element_impl<T, Value1, Value2, Tail...>
				: public sprout::tpp::detail::max_element_impl<T, sprout::tpp::detail::max_element_impl<T, Value1, Value2>::value, Tail...>
			{};
		}	// namespace detail
		//
		// max_element_c
		//
		template<typename T, T... Values>
		struct max_element_c
			: public sprout::tpp::detail::max_element_impl<T, Values...>
		{};
		//
		// max_element
		//
		template<typename... Types>
		struct max_element
			: public sprout::tpp::max_element_c<typename sprout::common_decay<decltype(Types::value)...>::type, Types::value...>
		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_MAX_ELEMENT_HPP
