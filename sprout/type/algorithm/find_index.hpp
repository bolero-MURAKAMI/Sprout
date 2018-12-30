/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
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
#include <sprout/type/algorithm/detail/find_index_result.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<
				typename Tuple, typename T, std::size_t First, std::size_t Last,
				std::size_t Pivot, std::size_t Found,
				bool C0 = (Found != First), bool C1 = (Pivot == 0)
			>
			struct find_index_impl;
			template<
				typename Tuple, typename T, std::size_t First, std::size_t Last,
				std::size_t Pivot, std::size_t Found,
				bool C1
			>
			struct find_index_impl<Tuple, T, First, Last, Pivot, Found, true, C1>
				: public sprout::types::detail::find_index_result<Tuple, Found>
			{};
			template<
				typename Tuple, typename T, std::size_t First, std::size_t Last,
				std::size_t Pivot, std::size_t Found
			>
			struct find_index_impl<Tuple, T, First, Last, Pivot, Found, false, true>
				: public sprout::types::detail::find_index_result<
					Tuple, (std::is_same<typename sprout::types::tuple_element<First, Tuple>::type, T>::value ? First : Last)
				>
			{};
			template<
				typename Tuple, typename T, std::size_t First, std::size_t Last,
				std::size_t Pivot, std::size_t Found
			>
			struct find_index_impl<Tuple, T, First, Last, Pivot, Found, false, false>
				: public sprout::types::detail::find_index_impl<
					Tuple, T, First + Pivot, Last,
					(Last - First - Pivot) / 2,
					sprout::types::detail::find_index_impl<
						Tuple, T, First, First + Pivot,
						Pivot / 2,
						First
					>::value
				>
			{};
			template<typename Tuple, typename T, std::size_t Size = sprout::types::tuple_size<Tuple>::value>
			struct find_index
				: public sprout::types::detail::find_index_impl<Tuple, T, 0, Size, Size / 2, 0>
			{};
			template<typename Tuple, typename T>
			struct find_index<Tuple, T, 0>
				: public sprout::types::detail::find_index_result<Tuple, 0>
			{};
		}	// namespace detail
		//
		// find_index
		//
		template<typename Tuple, typename T>
		struct find_index
			: public sprout::types::detail::find_index<Tuple, T>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename T>
		using find_index_t = typename sprout::types::find_index<Tuple, T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename Tuple, typename T>
		SPROUT_STATIC_CONSTEXPR std::size_t find_index_v = sprout::types::find_index<Tuple, T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_FIND_INDEX_HPP
