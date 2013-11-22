/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WEED_DETAIL_IS_SAME_ELEM_HPP
#define SPROUT_WEED_DETAIL_IS_SAME_ELEM_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/weed/traits/type/is_unused.hpp>
#include <sprout/weed/detail/is_same_container.hpp>
#include <sprout/weed/detail/is_container_and_elem.hpp>
#include <sprout/weed/detail/is_elem_and_container.hpp>
#include <sprout/weed/detail/is_both_tuple.hpp>
#include <sprout/weed/detail/is_tuple_and_elem.hpp>
#include <sprout/weed/detail/is_elem_and_tuple.hpp>

namespace sprout {
	namespace weed {
		namespace detail {
			template<typename T, typename U, typename = void>
			struct is_same_elem
				: public sprout::false_type
			{};
			template<typename T, typename U>
			struct is_same_elem<
				T,
				U,
				typename std::enable_if<
					std::is_same<T, U>::value
					&& !is_same_container<T, U>::value
					&& !is_container_and_elem<T, U>::value
					&& !is_elem_and_container<T, U>::value
					&& !is_both_tuple<T, U>::value
					&& !is_tuple_and_elem<T, U>::value
					&& !is_elem_and_tuple<T, U>::value
					&& !sprout::weed::traits::is_unused<T>::value
					&& !sprout::weed::traits::is_unused<U>::value
				>::type
			>
				: public sprout::true_type
			{};
		}	// namespace detail
	}	// namespace weed
}	// namespace sprout

#endif	// #ifndef SPROUT_WEED_DETAIL_IS_SAME_ELEM_HPP
