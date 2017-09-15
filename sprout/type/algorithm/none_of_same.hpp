/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_NONE_OF_SAME_HPP
#define SPROUT_TYPE_ALGORITHM_NONE_OF_SAME_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type/tuple.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<
				typename Tuple, typename T, std::size_t First, std::size_t Last,
				std::size_t Pivot,
				bool C1 = (Pivot == 0)
			>
			struct none_of_same_impl;
			template<
				typename Tuple, typename T, std::size_t First, std::size_t Last,
				std::size_t Pivot
			>
			struct none_of_same_impl<Tuple, T, First, Last, Pivot, true>
				: public sprout::bool_constant<
					!std::is_same<typename sprout::types::tuple_element<First, Tuple>::type, T>::value
				>
			{};
			template<
				typename Tuple, typename T, std::size_t First, std::size_t Last,
				std::size_t Pivot
			>
			struct none_of_same_impl<Tuple, T, First, Last, Pivot, false>
				: public sprout::bool_constant<
					sprout::types::detail::none_of_same_impl<
						Tuple, T, First, First + Pivot,
						Pivot / 2
					>::value
					&& sprout::types::detail::none_of_same_impl<
						Tuple, T, First + Pivot, Last,
						(Last - First - Pivot) / 2
					>::value
				>
			{};
			template<typename Tuple, typename T, std::size_t Size = sprout::types::tuple_size<Tuple>::value>
			struct none_of_same
				: public sprout::types::detail::none_of_same_impl<Tuple, T, 0, Size, Size / 2>
			{};
			template<typename Tuple, typename T>
			struct none_of_same<Tuple, T, 0>
				: public sprout::true_type
			{};
		}	// namespace detail
		//
		// none_of_same
		//
		template<typename Tuple, typename T>
		struct none_of_same
			: public sprout::types::detail::none_of_same<Tuple, T>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename T>
		using none_of_same_t = typename sprout::types::none_of_same<Tuple, T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename Tuple, typename T>
		SPROUT_STATIC_CONSTEXPR bool none_of_same_v = sprout::types::none_of_same<Tuple, T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_NONE_OF_SAME_HPP
