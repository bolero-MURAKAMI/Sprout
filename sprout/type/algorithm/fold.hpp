/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_FOLD_HPP
#define SPROUT_TYPE_ALGORITHM_FOLD_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<
				typename Tuple, typename T, typename BinaryOp, std::size_t I,
				bool Valid = (I != sprout::types::tuple_size<Tuple>::value)
			>
			struct fold_impl;
			template<typename Tuple, typename T, typename BinaryOp, std::size_t I>
			struct fold_impl<Tuple, T, BinaryOp, I, false>
				: public sprout::identity<T>
			{};
			template<typename Tuple, typename T, typename BinaryOp, std::size_t I>
			struct fold_impl<Tuple, T, BinaryOp, I, true>
				: public sprout::types::detail::fold_impl<
					Tuple,
					typename sprout::types::apply<BinaryOp, T, typename sprout::types::tuple_element<I, Tuple>::type>::type,
					BinaryOp,
					I + 1
				>
			{};
		}	// namespace detail
		//
		// fold
		//
		template<typename Tuple, typename T, typename BinaryOp>
		struct fold
			: public sprout::types::detail::fold_impl<Tuple, T, BinaryOp, 0>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename T, typename BinaryOp>
		using fold_t = typename sprout::types::fold<Tuple, T, BinaryOp>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_FOLD_HPP
