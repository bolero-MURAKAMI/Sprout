/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_PARTIAL_SUM_HPP
#define SPROUT_TYPE_ALGORITHM_PARTIAL_SUM_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/rebind_types.hpp>
#include <sprout/type/functional/plus.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<
				typename Tuple, typename BinaryOp, std::size_t I, std::size_t N, typename T, typename... Types
			>
			struct partial_sum_impl
				: public sprout::types::detail::partial_sum_impl<
					Tuple, BinaryOp, I + 1, N - 1,
					typename sprout::types::apply<BinaryOp, T, typename sprout::types::tuple_element<I, Tuple>::type>::type,
					Types..., T
				>
			{};
			template<typename Tuple, typename BinaryOp, std::size_t I, typename T, typename... Types>
			struct partial_sum_impl<Tuple, BinaryOp, I, 0, T, Types...>
				: public sprout::types::apply<sprout::types::rebind_types<Tuple>, Types..., T>
			{};

			template<typename Tuple, typename BinaryOp, std::size_t N>
			struct partial_sum
				: public sprout::types::detail::partial_sum_impl<Tuple, BinaryOp, 1, N - 1, typename sprout::types::tuple_element<0, Tuple>::type>
			{};
			template<typename Tuple, typename BinaryOp>
			struct partial_sum<Tuple, BinaryOp, 0>
				: public sprout::types::apply<sprout::types::rebind_types<Tuple> >
			{};
		}	// namespace detail
		//
		// partial_sum
		//
		template<typename Tuple, typename BinaryOp = sprout::types::plus_>
		struct partial_sum
			: public sprout::types::detail::partial_sum<Tuple, BinaryOp, sprout::types::tuple_size<Tuple>::value>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename BinaryOp = sprout::types::plus_>
		using partial_sum_t = typename sprout::types::partial_sum<Tuple, BinaryOp>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_PARTIAL_SUM_HPP
