/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_REBIND_TYPES_HPP
#define SPROUT_TYPE_REBIND_TYPES_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/index_tuple/index_t.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<typename Tuple>
			struct rebind_types_default {};
			template<template<typename...> class TupleClass, typename... Ts>
			struct rebind_types_default<TupleClass<Ts...> > {
			public:
				template<typename... Types>
				struct apply
					: public sprout::identity<TupleClass<Types...> >
				{};
			};
			template<template<typename VT, VT...> class IntegerSequenceClass, typename T, T... Vs>
			struct rebind_types_default<IntegerSequenceClass<T, Vs...> > {
			public:
				template<typename... Types>
				struct apply
					: public sprout::identity<IntegerSequenceClass<T, Types::value...> >
				{};
			};
			template<template<sprout::index_t...> class IndexTupleClass, sprout::index_t... Vs>
			struct rebind_types_default<IndexTupleClass<Vs...> > {
			public:
				template<typename... Types>
				struct apply
					: public sprout::identity<IndexTupleClass<Types::value...> >
				{};
			};
			template<template<sprout::uindex_t...> class UIndexTupleClass, sprout::uindex_t... Vs>
			struct rebind_types_default<UIndexTupleClass<Vs...> > {
			public:
				template<typename... Types>
				struct apply
					: public sprout::identity<UIndexTupleClass<Types::value...> >
				{};
			};
		}	// namespace detail

		//
		// rebind_types
		//
		template<typename Tuple>
		struct rebind_types
			: public sprout::types::detail::rebind_types_default<Tuple>
		{};

		template<typename Tuple>
		struct rebind_types<Tuple const> {
		public:
			template<typename... Types>
			struct apply {
			public:
				typedef typename sprout::types::rebind_types<
					Tuple
				>::template apply<
					Types...
				>::type const type;
			};
		};

		template<typename Tuple>
		struct rebind_types<Tuple volatile> {
		public:
			template<typename... Types>
			struct apply {
			public:
				typedef typename sprout::types::rebind_types<
					Tuple
				>::template apply<
					Types...
				>::type volatile type;
			};
		};

		template<typename Tuple>
		struct rebind_types<Tuple const volatile> {
		public:
			template<typename... Types>
			struct apply {
			public:
				typedef typename sprout::types::rebind_types<
					Tuple
				>::template apply<
					Types...
				>::type const volatile type;
			};
		};
	}	// namespace types

	using sprout::types::rebind_types;
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_REBIND_TYPES_HPP
