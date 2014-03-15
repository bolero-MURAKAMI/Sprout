/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_TUPLE_SIZE_HPP
#define SPROUT_TUPLE_TUPLE_TUPLE_SIZE_HPP

#include <cstddef>
#include <tuple>
#include <sprout/config.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>

namespace sprout {
	namespace tuples {
		//
		// tuple_size
		//
		template<typename T>
		struct tuple_size
			: public sprout::detail::type_traits_wrapper<std::tuple_size<T> >
		{};
		template<typename T>
		struct tuple_size<T const>
			: public sprout::tuples::tuple_size<T>
		{};
		template<typename T>
		struct tuple_size<T volatile>
			: public sprout::tuples::tuple_size<T>
		{};
		template<typename T>
		struct tuple_size<T const volatile>
			: public sprout::tuples::tuple_size<T>
		{};
	}	// namespace tuples

	using sprout::tuples::tuple_size;

#if SPROUT_USE_VARIABLE_TEMPLATES
	namespace tuples {
		template<typename T>
		SPROUT_STATIC_CONSTEXPR std::size_t tuple_size_v = sprout::tuples::tuple_size<T>::value;
	}	// namespace tuples

	using sprout::tuples::tuple_size_v;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TUPLE_SIZE_HPP
