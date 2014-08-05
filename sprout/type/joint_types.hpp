/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_JOINT_TYPES_HPP
#define SPROUT_TYPE_JOINT_TYPES_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/rebind_types.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<typename Tuple, typename Tup>
			struct joint_types_impl {
			private:
				template<typename IndexTuple1, typename IndexTuple2>
				struct apply_impl;
				template<sprout::index_t... Indexes1, sprout::index_t... Indexes2>
				struct apply_impl<sprout::index_tuple<Indexes1...>, sprout::index_tuple<Indexes2...> >
					: public sprout::types::rebind_types<
						Tuple
					>::template apply<
						typename sprout::types::tuple_element<Indexes1, Tuple>::type...,
						typename sprout::types::tuple_element<Indexes2, Tup>::type...
					>
				{};
			public:
				typedef typename apply_impl<
					typename sprout::tuple_indexes<Tuple>::type,
					typename sprout::tuple_indexes<Tup>::type
				>::type type;
			};

			template<typename Tuple>
			struct joint_types_default {};
			template<template<typename...> class TupleClass, typename... Ts>
			struct joint_types_default<TupleClass<Ts...> > {
			public:
				template<typename Tup>
				struct apply
					: public sprout::types::detail::joint_types_impl<TupleClass<Ts...>, Tup>
				{};
				template<typename... Types>
				struct apply<TupleClass<Types...> >
					: public sprout::identity<TupleClass<Ts..., Types...> >
				{};
			};
			template<template<typename VT, VT...> class ValueTupleClass, typename T, T... Vs>
			struct joint_types_default<ValueTupleClass<T, Vs...> > {
			public:
				template<typename Tup>
				struct apply
					: public sprout::types::detail::joint_types_impl<ValueTupleClass<T, Vs...>, Tup>
				{};
				template<T... Values>
				struct apply<ValueTupleClass<T, Values...> >
					: public sprout::identity<ValueTupleClass<T, Vs..., Values...> >
				{};
			};
		}	// namespace detail

		//
		// joint_types
		//
		template<typename Tuple>
		struct joint_types
			: public sprout::types::detail::joint_types_default<Tuple>
		{};

		template<typename Tuple>
		struct joint_types<Tuple const> {
		public:
			template<typename Tup>
			struct apply {
			public:
				typedef typename sprout::types::joint_types<
					Tuple
				>::template apply<
					Tup
				>::type const type;
			};
		};

		template<typename Tuple>
		struct joint_types<Tuple volatile> {
		public:
			template<typename Tup>
			struct apply {
			public:
				typedef typename sprout::types::joint_types<
					Tuple
				>::template apply<
					Tup
				>::type volatile type;
			};
		};

		template<typename Tuple>
		struct joint_types<Tuple const volatile> {
		public:
			template<typename Tup>
			struct apply {
			public:
				typedef typename sprout::types::joint_types<
					Tuple
				>::template apply<
					Tup
				>::type const volatile type;
			};
		};
	}	// namespace types

	using sprout::types::joint_types;
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_JOINT_TYPES_HPP
