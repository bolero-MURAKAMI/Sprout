/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_TUPLE_ELEMENT_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_ELEMENT_HPP

#include <type_traits>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/has_type.hpp>
#include <sprout/type_traits/has_value.hpp>
#include <sprout/detail/nil_base.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_element
		//
		namespace detail {
#if defined(_MSC_VER)
			template<std::size_t I, typename T, bool = true>
#else
			template<std::size_t I, typename T, bool = sprout::has_value<std::tuple_size<T> >::value>
#endif
			struct valid_tuple_index;
			template<std::size_t I, typename T>
			struct valid_tuple_index<I, T, false>
				: public sprout::false_type
			{};
			template<std::size_t I, typename T>
			struct valid_tuple_index<I, T, true>
				: public sprout::bool_constant<(I < std::tuple_size<T>::value)>
			{};

#if defined(_MSC_VER)
			template<std::size_t I, typename T, bool = true>
#else
			template<std::size_t I, typename T, bool = sprout::has_type<std::tuple_element<I, T> >::value && sprout::tuples::detail::valid_tuple_index<I, T>::value>
#endif
			struct tuple_element_default;
			template<std::size_t I, typename T>
			struct tuple_element_default<I, T, false>
				: public sprout::detail::nil_base
			{};
			template<std::size_t I, typename T>
			struct tuple_element_default<I, T, true>
				: public std::tuple_element<I, T>
			{};
		}	// namespace detail
		template<std::size_t I, typename T>
		struct tuple_element
			: public sprout::tuples::detail::tuple_element_default<I, T>
		{};

		namespace detail {
			template<std::size_t I, typename T>
			struct tuple_element_default<I, T const, true>
				: public std::add_const<
					typename sprout::tuples::tuple_element<I, T>::type
				>
			{};
			template<std::size_t I, typename T>
			struct tuple_element_default<I, T volatile, true>
				: public std::add_volatile<
					typename sprout::tuples::tuple_element<I, T>::type
				>
			{};
			template<std::size_t I, typename T>
			struct tuple_element_default<I, T const volatile, true>
				: public std::add_cv<
					typename sprout::tuples::tuple_element<I, T>::type
				>
			{};
		}	// namespace detail
		template<std::size_t I, typename T>
		struct tuple_element<I, T const>
			: public sprout::tuples::detail::tuple_element_default<I, T const>
		{};
		template<std::size_t I, typename T>
		struct tuple_element<I, T volatile>
			: public sprout::tuples::detail::tuple_element_default<I, T volatile>
		{};
		template<std::size_t I, typename T>
		struct tuple_element<I, T const volatile>
			: public sprout::tuples::detail::tuple_element_default<I, T const volatile>
		{};
	}	// namespace tuples

	using sprout::tuples::tuple_element;

#if SPROUT_USE_TEMPLATE_ALIASES
	namespace tuples {
		template<std::size_t I, typename T>
		using tuple_element_t = typename sprout::tuples::tuple_element<I, T>::type;
	}	// namespace tuples

	using sprout::tuples::tuple_element_t;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_ELEMENT_HPP
