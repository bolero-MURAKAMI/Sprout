/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_ALGORITHM_TRANSFORM_HPP
#define SPROUT_TYPE_ALGORITHM_TRANSFORM_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/rebind_types.hpp>
#include <sprout/type/map_types.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<typename Tuple1, typename Tuple2, typename BinaryOp, typename IndexTuple>
			struct transform2_impl;
			template<typename Tuple1, typename Tuple2, typename BinaryOp, sprout::index_t... Indexes>
			struct transform2_impl<Tuple1, Tuple2, BinaryOp, sprout::index_tuple<Indexes...> >
				: public sprout::types::apply<
					sprout::types::rebind_types<Tuple1>,
					typename sprout::types::apply<
						BinaryOp,
						typename sprout::types::tuple_element<Indexes, Tuple1>::type,
						typename sprout::types::tuple_element<Indexes, Tuple2>::type
					>::type...
				>
			{};
		}	// namespace detail
		//
		// transform
		//
		template<typename Tuple, typename Tuple2OrUnaryOp, typename BinaryOp = void>
		struct transform
			: public sprout::types::detail::transform2_impl<
				Tuple, Tuple2OrUnaryOp, BinaryOp,
				typename sprout::tuple_indexes<Tuple>::type
			>
		{};
		template<typename Tuple, typename UnaryOp>
		struct transform<Tuple, UnaryOp, void>
			: public sprout::types::apply<sprout::types::map_types<Tuple>, UnaryOp>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename Tuple2OrUnaryOp, typename BinaryOp = void>
		using transform_t = typename sprout::types::transform<Tuple, Tuple2OrUnaryOp, BinaryOp>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_ALGORITHM_TRANSFORM_HPP
