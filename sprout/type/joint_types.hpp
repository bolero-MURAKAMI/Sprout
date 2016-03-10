/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_JOINT_TYPES_HPP
#define SPROUT_TYPE_JOINT_TYPES_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>
#include <sprout/index_tuple/index_tuple.hpp>
#include <sprout/tuple/indexes.hpp>
#include <sprout/type/apply.hpp>
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
					: public sprout::types::apply<
						sprout::types::rebind_types<Tuple>,
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
			struct joint_types_default {
			public:
				template<typename Tup>
				struct apply
					: public sprout::types::detail::joint_types_impl<Tuple, Tup>
				{};
			};

			template<typename Tuple, typename Tup>
			struct joint_types_default_apply;

			template<
				template<typename...> class TupleClass, typename... Ts,
				typename Tup
			>
			struct joint_types_default_apply<TupleClass<Ts...>, Tup>
				: public sprout::types::detail::joint_types_impl<TupleClass<Ts...>, Tup>
			{};
			template<
				template<typename...> class TupleClass, typename... Ts,
				template<typename...> class TupClass, typename... Types
			>
			struct joint_types_default_apply<TupleClass<Ts...>, TupClass<Types...> >
				: public sprout::identity<TupleClass<Ts..., Types...> >
			{};
			template<
				template<typename...> class TupleClass, typename... Ts,
				template<typename VType, VType...> class IntSeqClass, typename Type, Type... Values
			>
			struct joint_types_default_apply<TupleClass<Ts...>, IntSeqClass<Type, Values...> >
				: public sprout::identity<TupleClass<Ts..., sprout::integral_constant<Type, Values>...> >
			{};
#define SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(TYPE) \
			template< \
				template<typename...> class TupleClass, typename... Ts, \
				template<TYPE...> class IntSeqClass, TYPE... Values \
			> \
			struct joint_types_default_apply<TupleClass<Ts...>, IntSeqClass<Values...> > \
				: public sprout::identity<TupleClass<Ts..., sprout::integral_constant<TYPE, Values>...> > \
			{}

			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(bool);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(char);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(signed char);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(unsigned char);
#if SPROUT_USE_UNICODE_LITERALS
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(char16_t);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(char32_t);
#endif
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(wchar_t);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(short);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(unsigned short);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(int);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(unsigned int);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(long);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(unsigned long);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(long long);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(unsigned long long);
#undef SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_TUPLE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE

			template<template<typename...> class TupleClass, typename... Ts>
			struct joint_types_default<TupleClass<Ts...> > {
			public:
				template<typename Tup>
				struct apply
					: public sprout::types::detail::joint_types_default_apply<TupleClass<Ts...>, Tup>
				{};
			};

			template<
				template<typename VT, VT...> class IntegerSequenceClass, typename T, T... Vs,
				typename Tup
			>
			struct joint_types_default_apply<IntegerSequenceClass<T, Vs...>, Tup>
				: public sprout::types::detail::joint_types_impl<IntegerSequenceClass<T, Vs...>, Tup>
			{};
			template<
				template<typename VT, VT...> class IntegerSequenceClass, typename T, T... Vs,
				template<typename...> class TupClass, typename... Types
			>
			struct joint_types_default_apply<IntegerSequenceClass<T, Vs...>, TupClass<Types...> >
				: public sprout::identity<IntegerSequenceClass<T, Vs..., Types::value...> >
			{};
			template<
				template<typename VT, VT...> class IntegerSequenceClass, typename T, T... Vs,
				template<typename VType, VType...> class IntSeqClass, typename Type, Type... Values
			>
			struct joint_types_default_apply<IntegerSequenceClass<T, Vs...>, IntSeqClass<Type, Values...> >
				: public sprout::identity<IntegerSequenceClass<T, Vs..., Values...> >
			{};
#define SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(TYPE) \
			template< \
				template<typename VT, VT...> class IntegerSequenceClass, typename T, T... Vs, \
				template<TYPE...> class IntSeqClass, TYPE... Values \
			> \
			struct joint_types_default_apply<IntegerSequenceClass<T, Vs...>, IntSeqClass<Values...> > \
				: public sprout::identity<IntegerSequenceClass<T, Vs..., Values...> > \
			{}
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(bool);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(char);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(signed char);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(unsigned char);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(char16_t);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(char32_t);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(wchar_t);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(short);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(unsigned short);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(int);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(unsigned int);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(long);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(unsigned long);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(long long);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(unsigned long long);
#undef SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_INTEGER_SEQUENCE_LIKE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE
			template<template<typename VT, VT...> class IntegerSequenceClass, typename T, T... Vs>
			struct joint_types_default<IntegerSequenceClass<T, Vs...> > {
			public:
				template<typename Tup>
				struct apply
					: public sprout::types::detail::joint_types_default_apply<IntegerSequenceClass<T, Vs...>, Tup>
				{};
			};

#define SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, TYPE) \
			template< \
				template<BASE...> class IntegerSequenceClass, BASE... Vs, \
				template<TYPE...> class IntSeqClass, TYPE... Values \
			> \
			struct joint_types_default_apply<IntegerSequenceClass<Vs...>, IntSeqClass<Values...> > \
				: public sprout::identity<IntegerSequenceClass<Vs..., Values...> > \
			{}
#if SPROUT_USE_UNICODE_LITERALS
#define SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_(BASE) \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, bool); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, char); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, signed char); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, unsigned char); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, char16_t); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, char32_t); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, wchar_t); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, short); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, unsigned short); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, int); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, unsigned int); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, long); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, unsigned long); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, long long); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, unsigned long long)
#else
#define SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_(BASE) \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, bool); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, char); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, signed char); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, unsigned char); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, wchar_t); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, short); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, unsigned short); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, int); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, unsigned int); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, long); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, unsigned long); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, long long); \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE(BASE, unsigned long long)
#endif
#define SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(BASE) \
			template< \
				template<BASE...> class IntegerSequenceClass, BASE... Vs, \
				typename Tup \
			> \
			struct joint_types_default_apply<IntegerSequenceClass<Vs...>, Tup> \
				: public sprout::types::detail::joint_types_impl<IntegerSequenceClass<Vs...>, Tup> \
			{}; \
			template< \
				template<BASE...> class IntegerSequenceClass, BASE... Vs, \
				template<typename...> class TupClass, typename... Types \
			> \
			struct joint_types_default_apply<IntegerSequenceClass<Vs...>, TupClass<Types...> > \
				: public sprout::identity<IntegerSequenceClass<Vs..., Types::value...> > \
			{}; \
			template< \
				template<BASE...> class IntegerSequenceClass, BASE... Vs, \
				template<typename VType, VType...> class IntSeqClass, typename Type, Type... Values \
			> \
			struct joint_types_default_apply<IntegerSequenceClass<Vs...>, IntSeqClass<Type, Values...> > \
				: public sprout::identity<IntegerSequenceClass<Vs..., Values...> > \
			{}; \
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_(BASE); \
			template<template<BASE...> class IntegerSequenceClass, BASE... Vs> \
			struct joint_types_default<IntegerSequenceClass<Vs...> > { \
			public: \
				template<typename Tup> \
				struct apply \
					: public sprout::types::detail::joint_types_default_apply<IntegerSequenceClass<Vs...>, Tup> \
				{}; \
			}
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(bool);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(char);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(signed char);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(unsigned char);
#if SPROUT_USE_UNICODE_LITERALS
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(char16_t);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(char32_t);
#endif
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(wchar_t);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(short);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(unsigned short);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(int);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(unsigned int);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(long);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(unsigned long);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(long long);
			SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL(unsigned long long);
#undef SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL_FOR_CERTAIN_INTEGER_SEQUENCE
#undef SPROUT_TYPES_DETAIL_JOINT_TYPES_DEFAULT_APPLY_CERTAIN_INTEGER_SEQUENCE_DECL
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
			struct apply
				: public sprout::identity<typename sprout::types::apply<sprout::types::joint_types<Tuple>, Tup>::type const>
			{};
		};

		template<typename Tuple>
		struct joint_types<Tuple volatile> {
		public:
			template<typename Tup>
			struct apply
				: public sprout::identity<typename sprout::types::apply<sprout::types::joint_types<Tuple>, Tup>::type volatile>
			{};
		};

		template<typename Tuple>
		struct joint_types<Tuple const volatile> {
		public:
			template<typename Tup>
			struct apply
				: public sprout::identity<typename sprout::types::apply<sprout::types::joint_types<Tuple>, Tup>::type const volatile>
			{};

		};
	}	// namespace types

	using sprout::types::joint_types;
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_JOINT_TYPES_HPP
