/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_FIND_INDEX_HPP
#define SPROUT_TYPE_ALGORITHM_FIND_INDEX_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<typename Tuple, typename T, std::size_t I, typename = void>
			struct find_index_impl;
			template<typename Tuple, typename T, std::size_t I>
			struct find_index_impl<
				Tuple, T, I,
				typename std::enable_if<
					I == sprout::types::tuple_size<Tuple>::value
					|| std::is_same<typename sprout::types::tuple_element<I, Tuple>::type, T>::value
				>::type
			>
				: public sprout::integral_constant<std::size_t, I>
			{};
			template<typename Tuple, typename T, std::size_t I>
			struct find_index_impl<
				Tuple, T, I,
				typename std::enable_if<
					I != sprout::types::tuple_size<Tuple>::value
					&& !std::is_same<typename sprout::types::tuple_element<I, Tuple>::type, T>::value
				>::type
			>
				: public sprout::types::detail::find_index_impl<Tuple, T, I + 1>
			{};
		}	// namespace detail
		//
		// find_index
		//
		template<typename Tuple, typename T>
		struct find_index
			: public sprout::types::detail::find_index_impl<Tuple, T, 0>
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_FIND_INDEX_HPP
