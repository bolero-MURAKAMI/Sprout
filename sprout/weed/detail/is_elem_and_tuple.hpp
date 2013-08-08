/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_DETAIL_IS_ELEM_AND_TUPLE_HPP
#define SPROUT_WEED_DETAIL_IS_ELEM_AND_TUPLE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/weed/traits/type/is_tuple.hpp>
#include <sprout/weed/traits/type/is_unused.hpp>

namespace sprout {
	namespace weed {
		namespace detail {
			template<typename T, typename U, typename = void>
			struct is_elem_and_tuple
				: public std::false_type
			{};
			template<typename T, typename U>
			struct is_elem_and_tuple<
				T,
				U,
				typename std::enable_if<
					!sprout::weed::traits::is_tuple<T>::value
					&& !sprout::weed::traits::is_unused<T>::value
					&& sprout::weed::traits::is_tuple<U>::value
				>::type
			>
				: public std::true_type
			{};
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_IS_ELEM_AND_TUPLE_HPP
