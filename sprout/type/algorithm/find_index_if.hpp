/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_FIND_INDEX_IF_HPP
#define SPROUT_TYPE_ALGORITHM_FIND_INDEX_IF_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/algorithm/detail/find_index_result.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<
				typename Tuple, typename Predicate, std::size_t First, std::size_t Last,
				std::size_t Pivot, std::size_t Found,
				bool C0 = (Found != First), bool C1 = (Pivot == 0)
			>
			struct find_index_if_impl;
			template<
				typename Tuple, typename Predicate, std::size_t First, std::size_t Last,
				std::size_t Pivot, std::size_t Found,
				bool C1
			>
			struct find_index_if_impl<Tuple, Predicate, First, Last, Pivot, Found, true, C1>
				: public sprout::types::detail::find_index_result<Tuple, Found>
			{};
			template<
				typename Tuple, typename Predicate, std::size_t First, std::size_t Last,
				std::size_t Pivot, std::size_t Found
			>
			struct find_index_if_impl<Tuple, Predicate, First, Last, Pivot, Found, false, true>
				: public sprout::types::detail::find_index_result<
					Tuple, (sprout::types::apply<Predicate, typename sprout::types::tuple_element<First, Tuple>::type>::type::value ? First : Last)
				>
			{};
			template<
				typename Tuple, typename Predicate, std::size_t First, std::size_t Last,
				std::size_t Pivot, std::size_t Found
			>
			struct find_index_if_impl<Tuple, Predicate, First, Last, Pivot, Found, false, false>
				: public sprout::types::detail::find_index_if_impl<
					Tuple, Predicate, First + Pivot, Last,
					(Last - First - Pivot) / 2,
					sprout::types::detail::find_index_if_impl<
						Tuple, Predicate, First, First + Pivot,
						Pivot / 2,
						First
					>::value
				>
			{};
			template<typename Tuple, typename Predicate, std::size_t Size = sprout::types::tuple_size<Tuple>::value>
			struct find_index_if
				: public sprout::types::detail::find_index_if_impl<Tuple, Predicate, 0, Size, Size / 2, 0>
			{};
			template<typename Tuple, typename Predicate>
			struct find_index_if<Tuple, Predicate, 0>
				: public sprout::types::detail::find_index_result<Tuple, 0>
			{};
		}	// namespace detail
		//
		// find_index_if
		//
		template<typename Tuple, typename Predicate>
		struct find_index_if
			: public sprout::types::detail::find_index_if<Tuple, Predicate>
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
