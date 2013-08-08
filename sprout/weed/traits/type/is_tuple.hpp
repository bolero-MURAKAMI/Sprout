/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_TRAITS_TYPE_IS_TUPLE_HPP
#define SPROUT_WEED_TRAITS_TYPE_IS_TUPLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/tuple.hpp>

namespace sprout {
	namespace weed {
		namespace traits {
			//
			// is_tuple
			//
			template<typename T>
			struct is_tuple
				: public std::false_type
			{};
			template<typename T>
			struct is_tuple<T const>
				: public sprout::weed::traits::is_tuple<T>
			{};
			template<typename T>
			struct is_tuple<T volatile>
				: public sprout::weed::traits::is_tuple<T>
			{};
			template<typename T>
			struct is_tuple<T const volatile>
				: public sprout::weed::traits::is_tuple<T>
			{};
			template<typename... Types>
			struct is_tuple<sprout::tuples::tuple<Types...> >
				: public std::true_type
			{};
		}	// namespace traits
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_TRAITS_TYPE_IS_TUPLE_HPP
