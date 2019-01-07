/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_NONE_OF_HPP
#define SPROUT_TYPE_ALGORITHM_NONE_OF_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/tuple.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<
				typename Tuple, typename Predicate, std::size_t First, std::size_t Last,
				std::size_t Pivot,
				bool C1 = (Pivot == 0)
			>
			struct none_of_impl;
			template<
				typename Tuple, typename Predicate, std::size_t First, std::size_t Last,
				std::size_t Pivot
			>
			struct none_of_impl<Tuple, Predicate, First, Last, Pivot, true>
				: public sprout::bool_constant<
					!sprout::types::apply<Predicate, typename sprout::types::tuple_element<First, Tuple>::type>::type::value
				>
			{};
			template<
				typename Tuple, typename Predicate, std::size_t First, std::size_t Last,
				std::size_t Pivot
			>
			struct none_of_impl<Tuple, Predicate, First, Last, Pivot, false>
				: public sprout::bool_constant<
					sprout::types::detail::none_of_impl<
						Tuple, Predicate, First, First + Pivot,
						Pivot / 2
					>::value
					&& sprout::types::detail::none_of_impl<
						Tuple, Predicate, First + Pivot, Last,
						(Last - First - Pivot) / 2
					>::value
				>
			{};
			template<typename Tuple, typename Predicate, std::size_t Size = sprout::types::tuple_size<Tuple>::value>
			struct none_of
				: public sprout::types::detail::none_of_impl<Tuple, Predicate, 0, Size, Size / 2>
			{};
			template<typename Tuple, typename Predicate>
			struct none_of<Tuple, Predicate, 0>
				: public sprout::true_type
			{};
		}	// namespace detail
		//
		// none_of
		//
		template<typename Tuple, typename Predicate>
		struct none_of
			: public sprout::types::detail::none_of<Tuple, Predicate>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename Predicate>
		using none_of_t = typename sprout::types::none_of<Tuple, Predicate>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename Tuple, typename Predicate>
		SPROUT_STATIC_CONSTEXPR bool none_of_v = sprout::types::none_of<Tuple, Predicate>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_NONE_OF_HPP
