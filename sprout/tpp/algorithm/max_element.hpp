/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TPP_ALGORITHM_MAX_ELEMENT_HPP
#define SPROUT_TPP_ALGORITHM_MAX_ELEMENT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type/type_tuple.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<typename T, typename U>
			struct max_value
				: public std::conditional<(T::value < U::value), U, T>
			{};

			template<typename Tup, std::size_t First, std::size_t Last, bool = (Last - First == 1)>
			struct max_element_impl
				: public std::tuple_element<First, Tup>::type
			{};
			template<typename Tup, std::size_t First, std::size_t Last>
			struct max_element_impl<Tup, First, Last, false>
				: public sprout::tpp::detail::max_value<
					typename sprout::tpp::detail::max_element_impl<Tup, First, (First + Last) / 2>::type,
					typename sprout::tpp::detail::max_element_impl<Tup, (First + Last) / 2, Last>::type
				>::type
			{};
		}	// namespace detail
		//
		// max_element
		//
		template<typename... Types>
		struct max_element
			: public sprout::tpp::detail::max_element_impl<sprout::types::type_tuple<Types...>, 0, sizeof...(Types)>
		{};
		//
		// max_element_c
		//
		template<typename T, T... Values>
		struct max_element_c
			: public sprout::tpp::max_element<sprout::integral_constant<T, Values>...>
		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_MAX_ELEMENT_HPP
