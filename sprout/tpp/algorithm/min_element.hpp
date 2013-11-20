/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TPP_ALGORITHM_MIN_ELEMENT_HPP
#define SPROUT_TPP_ALGORITHM_MIN_ELEMENT_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/common_decay.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<typename T, T... Values>
			struct min_element_impl;
			template<typename T, T Value>
			struct min_element_impl<T, Value>
				: public sprout::integral_constant<T, Value>
			{};
			template<typename T, T Value1, T Value2>
			struct min_element_impl<T, Value1, Value2>
				: public sprout::integral_constant<T, (Value2 < Value1 ? Value2 : Value1)>
			{};
			template<typename T, T Value1, T Value2, T... Tail>
			struct min_element_impl<T, Value1, Value2, Tail...>
				: public sprout::tpp::detail::min_element_impl<T, sprout::tpp::detail::min_element_impl<T, Value1, Value2>::value, Tail...>
			{};
		}	// namespace detail
		//
		// min_element_c
		//
		template<typename T, T... Values>
		struct min_element_c
			: public sprout::tpp::detail::min_element_impl<T, Values...>
		{};
		//
		// min_element
		//
		template<typename... Types>
		struct min_element
			: public sprout::tpp::min_element_c<typename sprout::common_decay<decltype(Types::value)...>::type, Types::value...>
		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_MIN_ELEMENT_HPP
