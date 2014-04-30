/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
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

namespace sprout {
	namespace tuples {
		//
		// tuple_element
		//
		template<std::size_t I, typename T>
		struct tuple_element
			: public std::tuple_element<I, T>
		{};
		template<std::size_t I, typename T>
		struct tuple_element<I, T const>
			: public std::add_const<
				typename sprout::tuples::tuple_element<I, T>::type
			>
		{};
		template<std::size_t I, typename T>
		struct tuple_element<I, T volatile>
			: public std::add_volatile<
				typename sprout::tuples::tuple_element<I, T>::type
			>
		{};
		template<std::size_t I, typename T>
		struct tuple_element<I, T const volatile>
			: public std::add_cv<
				typename sprout::tuples::tuple_element<I, T>::type
			>
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
