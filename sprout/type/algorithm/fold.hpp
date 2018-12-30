/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_FOLD_HPP
#define SPROUT_TYPE_ALGORITHM_FOLD_HPP

#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<
				typename Tuple, typename T, typename BinaryOp, std::size_t First, std::size_t Last,
				std::size_t Pivot,
				bool C0 = (Pivot == 0)
			>
			struct fold_impl;
			template<
				typename Tuple, typename T, typename BinaryOp, std::size_t First, std::size_t Last,
				std::size_t Pivot
			>
			struct fold_impl<Tuple, T, BinaryOp, First, Last, Pivot, true>
				: public sprout::types::apply<BinaryOp, T, typename sprout::types::tuple_element<First, Tuple>::type>
			{};
			template<
				typename Tuple, typename T, typename BinaryOp, std::size_t First, std::size_t Last,
				std::size_t Pivot
			>
			struct fold_impl<Tuple, T, BinaryOp, First, Last, Pivot, false>
				: public sprout::types::detail::fold_impl<
					Tuple,
					typename sprout::types::detail::fold_impl<
						Tuple,
						T,
						BinaryOp,
						First, First + Pivot,
						Pivot / 2
					>::type,
					BinaryOp,
					First + Pivot, Last,
					(Last - First - Pivot) / 2
				>
			{};
			template<typename Tuple, typename T, typename BinaryOp, std::size_t Size = sprout::types::tuple_size<Tuple>::value>
			struct fold
				: public sprout::types::detail::fold_impl<Tuple, T, BinaryOp, 0, Size, Size / 2>
			{};
			template<typename Tuple, typename T, typename BinaryOp>
			struct fold<Tuple, T, BinaryOp, 0>
				: public sprout::identity<T>
			{};
		}	// namespace detail
		//
		// fold
		//
		template<typename Tuple, typename T, typename BinaryOp>
		struct fold
			: public sprout::types::detail::fold<Tuple, T, BinaryOp>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename T, typename BinaryOp>
		using fold_t = typename sprout::types::fold<Tuple, T, BinaryOp>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_FOLD_HPP
