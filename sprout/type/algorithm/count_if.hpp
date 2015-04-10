/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_COUNT_IF_HPP
#define SPROUT_TYPE_ALGORITHM_COUNT_IF_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<
				typename Tuple, typename Predicate, std::size_t First,
				std::size_t Size,
				bool C0 = (Size == 1)
			>
			struct count_if_impl;
			template<
				typename Tuple, typename Predicate, std::size_t First,
				std::size_t Size
			>
			struct count_if_impl<Tuple, Predicate, First, Size, true>
				: public sprout::integral_constant<
					std::size_t, (sprout::types::apply<Predicate, typename sprout::types::tuple_element<First, Tuple>::type>::type::value ? 1 : 0)
				>
			{};
			template<
				typename Tuple, typename Predicate, std::size_t First,
				std::size_t Size
			>
			struct count_if_impl<Tuple, Predicate, First, Size, false>
				: public sprout::integral_constant<
					std::size_t,
					sprout::types::detail::count_if_impl<
						Tuple, Predicate, First,
						Size / 2
					>::value
						+ sprout::types::detail::count_if_impl<
							Tuple, Predicate, First + Size / 2,
							Size - Size / 2
						>::value
				>
			{};
			template<typename Tuple, typename Predicate, std::size_t Size = sprout::types::tuple_size<Tuple>::value>
			struct count_if
				: public sprout::types::detail::count_if_impl<Tuple, Predicate, 0, Size>
			{};
			template<typename Tuple, typename Predicate>
			struct count_if<Tuple, Predicate, 0>
				: public sprout::integral_constant<std::size_t, 0>
			{};
		}	// namespace detail
		//
		// count_if
		//
		template<typename Tuple, typename Predicate>
		struct count_if
			: public sprout::types::detail::count_if<Tuple, Predicate>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename Predicate>
		using count_if_t = typename sprout::types::count_if<Tuple, Predicate>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename Tuple, typename Predicate>
		SPROUT_STATIC_CONSTEXPR std::size_t count_if_v = sprout::types::count_if<Tuple, Predicate>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_COUNT_IF_HPP
