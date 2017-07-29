/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_COUNT_HPP
#define SPROUT_TYPE_ALGORITHM_COUNT_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<
				typename Tuple, typename T, std::size_t First,
				std::size_t Size,
				bool C0 = (Size == 1)
			>
			struct count_impl;
			template<
				typename Tuple, typename T, std::size_t First,
				std::size_t Size
			>
			struct count_impl<Tuple, T, First, Size, true>
				: public sprout::integral_constant<
					std::size_t, (std::is_same<typename sprout::types::tuple_element<First, Tuple>::type, T>::value ? 1 : 0)
				>
			{};
			template<
				typename Tuple, typename T, std::size_t First,
				std::size_t Size
			>
			struct count_impl<Tuple, T, First, Size, false>
				: public sprout::integral_constant<
					std::size_t,
					sprout::types::detail::count_impl<
						Tuple, T, First,
						Size / 2
					>::value
						+ sprout::types::detail::count_impl<
							Tuple, T, First + Size / 2,
							Size - Size / 2
						>::value
				>
			{};
			template<typename Tuple, typename T, std::size_t Size = sprout::types::tuple_size<Tuple>::value>
			struct count
				: public sprout::types::detail::count_impl<Tuple, T, 0, Size>
			{};
			template<typename Tuple, typename T>
			struct count<Tuple, T, 0>
				: public sprout::integral_constant<std::size_t, 0>
			{};
		}	// namespace detail
		//
		// count
		//
		template<typename Tuple, typename T>
		struct count
			: public sprout::types::detail::count<Tuple, T>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename T>
		using count_t = typename sprout::types::count<Tuple, T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename Tuple, typename T>
		SPROUT_STATIC_CONSTEXPR std::size_t count_v = sprout::types::count<Tuple, T>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_COUNT_HPP
