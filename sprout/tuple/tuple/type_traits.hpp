/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_TUPLE_TYPE_TRAITS_HPP
#define SPROUT_TUPLE_TUPLE_TYPE_TRAITS_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple/tuple_fwd.hpp>

namespace sprout {
	namespace tuples {
		//
		// is_tuple
		//
		template<typename T>
		struct is_tuple
			: public std::false_type
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
			: public std::true_type
		{};
	}	// namespace tuples

	using sprout::tuples::is_tuple;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_TUPLE_TYPE_TRAITS_HPP
