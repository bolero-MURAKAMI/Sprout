/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_POP_FRONT_TYPES_HPP
#define SPROUT_TYPE_POP_FRONT_TYPES_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/rebind_types.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<typename Tuple>
			struct pop_front_types_default {
				template<typename IndexTuple>
				struct apply_impl;
				template<sprout::index_t... Indexes>
				struct apply_impl<sprout::index_tuple<Indexes...> >
					: public sprout::types::apply<
						sprout::types::rebind_types<Tuple>,
						typename sprout::types::tuple_element<Indexes, Tuple>::type...
					>
				{};
			public:
				template<typename = void>
				struct apply
					: public apply_impl<typename sprout::index_range<1, sprout::types::tuple_size<Tuple>::value>::type>
				{};
			};
			template<template<typename...> class TupleClass, typename Head, typename... Tail>
			struct pop_front_types_default<TupleClass<Head, Tail...> > {
			public:
				template<typename = void>
				struct apply
					: public sprout::identity<TupleClass<Tail...> >
				{};
			};
			template<template<typename VT, VT...> class IntegerSequenceClass, typename T, T Head, T... Tail>
			struct pop_front_types_default<IntegerSequenceClass<T, Head, Tail...> > {
			public:
				template<typename = void>
				struct apply
					: public sprout::identity<IntegerSequenceClass<T, Tail...> >
				{};
			};

#define SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(TYPE) \
			template<template<TYPE...> class IndexTupleClass, TYPE Head, TYPE... Tail> \
			struct pop_front_types_default<IndexTupleClass<Head, Tail...> > { \
			public: \
				template<typename = void> \
				struct apply \
					: public sprout::identity<IndexTupleClass<Tail...> > \
				{}; \
			}

			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(bool);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(char);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(signed char);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(unsigned char);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(char16_t);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(char32_t);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(wchar_t);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(short);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(unsigned short);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(int);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(unsigned int);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(long);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(unsigned long);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(long long);
			SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(unsigned long long);

#undef SPROUT_TYPES_DETAIL_POP_FRONT_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL
		}	// namespace detail

		//
		// pop_front_types
		//
		template<typename Tuple>
		struct pop_front_types
			: public sprout::types::detail::pop_front_types_default<Tuple>
		{};

		template<typename Tuple>
		struct pop_front_types<Tuple const> {
		public:
			template<typename... Types>
			struct apply
				: public sprout::identity<typename sprout::types::apply<sprout::types::pop_front_types<Tuple>, Types...>::type const>
			{};
		};

		template<typename Tuple>
		struct pop_front_types<Tuple volatile> {
		public:
			template<typename... Types>
			struct apply
				: public sprout::identity<typename sprout::types::apply<sprout::types::pop_front_types<Tuple>, Types...>::type volatile>
			{};
		};

		template<typename Tuple>
		struct pop_front_types<Tuple const volatile> {
		public:
			template<typename... Types>
			struct apply
				: public sprout::identity<typename sprout::types::apply<sprout::types::pop_front_types<Tuple>, Types...>::type const volatile>
			{};
		};
	}	// namespace types

	using sprout::types::pop_front_types;
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_POP_FRONT_TYPES_HPP
