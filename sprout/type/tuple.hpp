/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TUPLE_HPP
#define SPROUT_TYPE_TUPLE_HPP

#include <tuple>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>
#include <sprout/tuple/tuple/tuple_element.hpp>

namespace sprout {
	namespace types {
		//
		// begin
		//
		template<typename T, typename Enable = void>
		struct begin {
			typedef typename T::begin type;
		};
		//
		// end
		//
		template<typename T, typename Enable = void>
		struct end {
			typedef typename T::end type;
		};

		//
		// tuple_size
		//
		template<typename T, typename Enable = void>
		struct tuple_size
			: public sprout::detail::type_traits_wrapper<std::tuple_size<T> >
		{};
		//
		// tuple_element
		//
		template<std::size_t I, typename T, typename Enable = void>
		struct tuple_element
			: public sprout::tuples::tuple_element<I, T>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename T>
		using begin_t = typename sprout::types::begin<T>::type;
		template<typename T>
		using end_t = typename sprout::types::end<T>::type;

		template<std::size_t I, typename T>
		using tuple_element_t = typename sprout::types::tuple_element<I, T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename Tuple>
		SPROUT_STATIC_CONSTEXPR std::size_t tuple_size_v = sprout::types::tuple_size<Tuple>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_TUPLE_HPP
