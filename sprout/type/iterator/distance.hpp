/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ITERATOR_DISTANCE_HPP
#define SPROUT_TYPE_ITERATOR_DISTANCE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
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

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename First, typename Last>
		using distance_t = typename sprout::types::distance<First, Last>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename First, typename Last>
		SPROUT_STATIC_CONSTEXPR std::size_t distance_v = sprout::types::distance<First, Last>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ITERATOR_DISTANCE_HPP
