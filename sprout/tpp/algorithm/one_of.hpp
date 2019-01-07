/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TPP_ALGORITHM_ONE_OF_HPP
#define SPROUT_TPP_ALGORITHM_ONE_OF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type/type_tuple.hpp>

namespace sprout {
	namespace tpp {
		namespace detail {
			template<typename Tup, std::size_t First, std::size_t Last, bool = (Last - First == 1)>
			struct one_of_impl_1
				: public sprout::bool_constant<!std::tuple_element<First, Tup>::type::value>
			{};
			template<typename Tup, std::size_t First, std::size_t Last>
			struct one_of_impl_1<Tup, First, Last, false>
				: public sprout::bool_constant<
					sprout::tpp::detail::one_of_impl_1<Tup, First, (First + Last) / 2>::value
						&& sprout::tpp::detail::one_of_impl_1<Tup, (First + Last) / 2, Last>::value
				>
			{};

			template<typename Tup, std::size_t First, std::size_t Last, bool = (Last - First == 1)>
			struct one_of_impl
				: public std::tuple_element<First, Tup>::type
			{};
			template<typename Tup, std::size_t First, std::size_t Last>
			struct one_of_impl<Tup, First, Last, false>
				: public sprout::bool_constant<
					sprout::tpp::detail::one_of_impl<Tup, First, (First + Last) / 2>::value
						? sprout::tpp::detail::one_of_impl_1<Tup, (First + Last) / 2, Last>::value
						: sprout::tpp::detail::one_of_impl<Tup, (First + Last) / 2, Last>::value
				>
			{};
		}	// namespace detail
		//
		// one_of
		//
		template<typename... Types>
		struct one_of
			: public sprout::tpp::detail::one_of_impl<sprout::types::type_tuple<Types...>, 0, sizeof...(Types)>
		{};
		template<>
		struct one_of<>
			: public sprout::false_type
		{};
		//
		// one_of_c
		//
		template<bool... Values>
		struct one_of_c
			: public sprout::tpp::one_of<sprout::bool_constant<Values>...>
		{};
//		namespace detail {
//			template<bool... Values>
//			struct one_of_impl;
//			template<>
//			struct one_of_impl<>
//				: public sprout::false_type
//			{};
//			template<>
//			struct one_of_impl<true>
//				: public sprout::true_type
//			{};
//			template<>
//			struct one_of_impl<false>
//				: public sprout::false_type
//			{};
//			template<bool... Tail>
//			struct one_of_impl<true, Tail...>
//				: public sprout::tpp::none_of_c<Tail...>
//			{};
//			template<bool... Tail>
//			struct one_of_impl<false, Tail...>
//				: public sprout::bool_constant<sprout::tpp::detail::one_of_impl<Tail...>::value>
//			{};
//		}	// namespace detail
//		//
//		// one_of_c
//		//
//		template<bool... Values>
//		struct one_of_c
//			: public sprout::tpp::detail::one_of_impl<Values...>
//		{};
//		//
//		// one_of
//		//
//		template<typename... Types>
//		struct one_of
//			: public sprout::tpp::one_of_c<Types::value...>
//		{};
	}	// namespace tpp
}	// namespace sprout

#endif	// #ifndef SPROUT_TPP_ALGORITHM_ONE_OF_HPP
