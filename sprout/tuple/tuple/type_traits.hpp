/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_TYPE_TRAITS_HPP
#define SPROUT_TUPLE_TUPLE_TYPE_TRAITS_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple/tuple_fwd.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace tuples {
		//
		// is_tuple
		//
		template<typename T>
		struct is_tuple
			: public sprout::false_type
		{};
		template<typename T>
		struct is_tuple<T const>
			: public sprout::tuples::is_tuple<T>
		{};
		template<typename T>
		struct is_tuple<T const volatile>
			: public sprout::tuples::is_tuple<T>
		{};
		template<typename... Types>
		struct is_tuple<sprout::tuples::tuple<Types...> >
			: public sprout::true_type
		{};
	}	// namespace tuples

	using sprout::tuples::is_tuple;

#if SPROUT_USE_VARIABLE_TEMPLATES
	namespace tuples {
		template<typename T>
		SPROUT_STATIC_CONSTEXPR bool is_tuple_v = sprout::tuples::is_tuple<T>::value;
	}	// namespace tuples

	using sprout::tuples::is_tuple;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TYPE_TRAITS_HPP
