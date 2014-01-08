/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ITERATOR_DISTANCE_HPP
#define SPROUT_TYPE_ITERATOR_DISTANCE_HPP

#include <cstddef>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type/iterator/next.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace types {
		//
		// distance
		//
		namespace detail {
			template<typename First, typename Last, std::ptrdiff_t N, typename = void>
			struct distance_impl;
			template<typename First, typename Last, std::ptrdiff_t N>
			struct distance_impl<
				First,
				Last,
				N,
				typename std::enable_if<
					std::is_same<First, Last>::value
				>::type
			>
				: public sprout::integral_constant<std::ptrdiff_t, N>
			{};
			template<typename First, typename Last, std::ptrdiff_t N>
			struct distance_impl<
				First,
				Last,
				N,
				typename std::enable_if<
					!std::is_same<First, Last>::value
				>::type
			>
				: public sprout::types::detail::distance_impl<
					typename sprout::types::next<First>::type,
					Last,
					N + 1
				>
			{};
		}	// namespace detail
		template<typename First, typename Last>
		struct distance
			: public sprout::types::detail::distance_impl<First, Last, 0>
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_DISTANCE_HPP
