/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_TUPLE_TRAITS_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_TRAITS_HPP

#include <tuple>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/tuple/tuple/tuple_size.hpp>
#include <sprout/tuple/tuple/tuple_element.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_traits
		//
		template<typename Tuple>
		struct tuple_traits {
		public:
			SPROUT_STATIC_CONSTEXPR std::size_t size = sprout::tuples::tuple_size<Tuple>::value;
		public:
			template<std::size_t I>
			struct element
				: public sprout::tuples::tuple_element<I, Tuple>
			{};
			template<std::size_t I>
			struct lvalue_reference
				: public std::add_lvalue_reference<typename element<I>::type>
			{};
			template<std::size_t I>
			struct const_lvalue_reference
				: public std::add_lvalue_reference<typename element<I>::type const>
			{};
			template<std::size_t I>
			struct rvalue_reference
				: public std::add_rvalue_reference<typename element<I>::type>
			{};
			template<std::size_t I>
			struct const_rvalue_reference
				: public std::add_rvalue_reference<typename element<I>::type const>
			{};
		};
		template<typename Tuple>
		SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::tuples::tuple_traits<Tuple>::size;

		template<typename Tuple>
		struct tuple_traits<Tuple const> {
		public:
			SPROUT_STATIC_CONSTEXPR std::size_t size = sprout::tuples::tuple_traits<Tuple>::size;
		public:
			template<std::size_t I>
			struct element
				: public sprout::tuples::tuple_traits<Tuple>::template element<I>
			{};
			template<std::size_t I>
			struct lvalue_reference
				: public sprout::tuples::tuple_traits<Tuple>::template const_lvalue_reference<I>
			{};
			template<std::size_t I>
			struct const_lvalue_reference
				: public sprout::tuples::tuple_traits<Tuple>::template const_lvalue_reference<I>
			{};
			template<std::size_t I>
			struct rvalue_reference
				: public sprout::tuples::tuple_traits<Tuple>::template const_rvalue_reference<I>
			{};
			template<std::size_t I>
			struct const_rvalue_reference
				: public sprout::tuples::tuple_traits<Tuple>::template const_rvalue_reference<I>
			{};
		};
		template<typename Tuple>
		SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::tuples::tuple_traits<Tuple const>::size;
	}	// namespace tuples

	using sprout::tuples::tuple_traits;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_TRAITS_HPP
