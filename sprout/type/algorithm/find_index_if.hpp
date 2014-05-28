/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_FIND_INDEX_IF_HPP
#define SPROUT_TYPE_ALGORITHM_FIND_INDEX_IF_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<typename Tuple, typename Predicate, std::size_t I, typename = void>
			struct find_index_if_impl;
			template<typename Tuple, typename Predicate, std::size_t I>
			struct find_index_if_impl<
				Tuple, Predicate, I,
				typename std::enable_if<
					I == sprout::types::tuple_size<Tuple>::value
					|| Predicate::template apply<typename sprout::types::tuple_element<I, Tuple>::type>::type::value
				>::type
			>
				: public sprout::integral_constant<std::size_t, I>
			{};
			template<typename Tuple, typename Predicate, std::size_t I>
			struct find_index_if_impl<
				Tuple, Predicate, I,
				typename std::enable_if<
					I != sprout::types::tuple_size<Tuple>::value
					&& !Predicate::template apply<typename sprout::types::tuple_element<I, Tuple>::type>::type::value
				>::type
			>
				: public sprout::types::detail::find_index_if_impl<Tuple, Predicate, I + 1>
			{};
		}	// namespace detail
		//
		// find_index_if
		//
		template<typename Tuple, typename Predicate>
		struct find_index_if
			: public sprout::types::detail::find_index_if_impl<Tuple, Predicate, 0>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename Predicate>
		using find_index_if_t = typename sprout::types::find_index_if<Tuple, Predicate>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename Tuple, typename Predicate>
		SPROUT_STATIC_CONSTEXPR std::size_t find_index_if_v = sprout::types::find_index_if<Tuple, Predicate>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_FIND_INDEX_IF_HPP
