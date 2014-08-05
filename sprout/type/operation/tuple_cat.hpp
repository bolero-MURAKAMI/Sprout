/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_TUPLE_CAT_HPP
#define SPROUT_TYPE_OPERATION_TUPLE_CAT_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/index_tuple.hpp>
#include <sprout/type/joint_types.hpp>
#include <sprout/type/type_tuple.hpp>
#include <sprout/type/tuple.hpp>

namespace sprout {
	namespace types {
		//
		// tuple_cat
		//
		namespace detail {
			template<typename Tuples, typename LIndexTuple, typename RIndexTuple>
			struct tuple_cat_impl;
			template<typename Tuples, sprout::index_t... LIndexes, sprout::index_t... RIndexes>
			struct tuple_cat_impl<Tuples, sprout::index_tuple<LIndexes...>, sprout::index_tuple<RIndexes...> >
				: public sprout::types::joint_types<
					typename sprout::types::detail::tuple_cat_impl<
						sprout::types::type_tuple<typename sprout::types::tuple_element<LIndexes, Tuples>::type...>,
						typename sprout::index_range<0, sizeof...(LIndexes) / 2>::type,
						typename sprout::index_range<sizeof...(LIndexes) / 2, sizeof...(LIndexes)>::type
					>::type
				>::template apply<
					typename sprout::types::detail::tuple_cat_impl<
						sprout::types::type_tuple<typename sprout::types::tuple_element<RIndexes, Tuples>::type...>,
						typename sprout::index_range<0, sizeof...(RIndexes) / 2>::type,
						typename sprout::index_range<sizeof...(RIndexes) / 2, sizeof...(RIndexes)>::type
					>::type
				>
			{};
			template<typename Tuples>
			struct tuple_cat_impl<Tuples, sprout::index_tuple<>, sprout::index_tuple<0> >
				: public sprout::types::tuple_element<0, Tuples>
			{};
			template<typename Tuples>
			struct tuple_cat_impl<Tuples, sprout::index_tuple<>, sprout::index_tuple<> >
				: public sprout::identity<sprout::types::type_tuple<> >
			{};
		}	// namespace detail
		template<typename... Tuples>
		struct tuple_cat
			: public sprout::types::detail::tuple_cat_impl<
				sprout::types::type_tuple<Tuples...>,
				typename sprout::index_range<0, sizeof...(Tuples) / 2>::type,
				typename sprout::index_range<sizeof...(Tuples) / 2, sizeof...(Tuples)>::type
			>
		{};
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_TUPLE_CAT_HPP
