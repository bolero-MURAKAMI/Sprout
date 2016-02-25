/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_MAP_TYPES_HPP
#define SPROUT_TYPE_MAP_TYPES_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/rebind_types.hpp>

namespace sprout {
	namespace types {
		namespace detail {
			template<typename Tuple>
			struct map_types_default {
			private:
				template<typename Op, typename IndexTuple>
				struct apply_impl;
				template<typename Op, sprout::index_t... Indexes>
				struct apply_impl<Op, sprout::index_tuple<Indexes...> >
					: public sprout::types::apply<
						sprout::types::rebind_types<Tuple>,
						typename sprout::types::apply<Op, typename sprout::types::tuple_element<Indexes, Tuple>::type>::type...
					>
				{};
			public:
				template<typename Op>
				struct apply
					: public apply_impl<Op, typename sprout::tuple_indexes<Tuple>::type>
				{};
			};
			template<template<typename...> class TupleClass, typename... Ts>
			struct map_types_default<TupleClass<Ts...> > {
			public:
				template<typename Op>
				struct apply
					: public sprout::identity<TupleClass<typename sprout::types::apply<Op, Ts>::type...> >
				{};
			};
			template<template<typename VT, VT...> class IntegerSequenceClass, typename T, T... Vs>
			struct map_types_default<IntegerSequenceClass<T, Vs...> > {
			public:
				template<typename Op>
				struct apply
					: public sprout::identity<IntegerSequenceClass<T, sprout::types::apply<Op, sprout::integral_constant<T, Vs> >::type::value...> >
				{};
			};

#define SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(TYPE) \
			template<template<TYPE...> class IndexTupleClass, TYPE... Vs> \
			struct map_types_default<IndexTupleClass<Vs...> > { \
			public: \
				template<typename Op> \
				struct apply \
					: public sprout::identity<IndexTupleClass<sprout::types::apply<Op, sprout::integral_constant<TYPE, Vs> >::type::value...> > \
				{}; \
			}

			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(bool);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(char);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(signed char);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(unsigned char);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(char16_t);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(char32_t);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(wchar_t);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(short);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(unsigned short);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(int);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(unsigned int);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(long);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(unsigned long);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(long long);
			SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL(unsigned long long);

#undef SPROUT_TYPES_DETAIL_MAP_TYPES_DEFAULT_INTEGER_SEQUENCE_LIKE_DECL
		}	// namespace detail

		//
		// map_types
		//
		template<typename Tuple>
		struct map_types
			: public sprout::types::detail::map_types_default<Tuple>
		{};

		template<typename Tuple>
		struct map_types<Tuple const> {
		public:
			template<typename Op>
			struct apply
				: public sprout::identity<typename sprout::types::apply<sprout::types::map_types<Tuple>, Op>::type const>
			{};
		};

		template<typename Tuple>
		struct map_types<Tuple volatile> {
		public:
			template<typename Op>
			struct apply
				: public sprout::identity<typename sprout::types::apply<sprout::types::map_types<Tuple>, Op>::type volatile>
			{};
		};

		template<typename Tuple>
		struct map_types<Tuple const volatile> {
		public:
			template<typename Op>
			struct apply
				: public sprout::identity<typename sprout::types::apply<sprout::types::map_types<Tuple>, Op>::type const volatile>
			{};
		};
	}	// namespace types

	using sprout::types::map_types;
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_MAP_TYPES_HPP
