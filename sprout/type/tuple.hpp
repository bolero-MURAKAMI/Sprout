/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TUPLE_HPP
#define SPROUT_TYPE_TUPLE_HPP

#include <tuple>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/detail/type_traits_wrapper.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/has_type.hpp>
#include <sprout/type_traits/has_value.hpp>
#include <sprout/tuple/tuple/tuple_size.hpp>
#include <sprout/tuple/tuple/tuple_element.hpp>
#include <sprout/type/type_tuple_decl.hpp>
#include <sprout/detail/nil_base.hpp>

namespace sprout {
	namespace types {
		//
		// begin
		//
		template<typename T, typename Enable = void>
		struct begin {
			typedef typename T::begin type;
		};
		//
		// end
		//
		template<typename T, typename Enable = void>
		struct end {
			typedef typename T::end type;
		};

		//
		// tuple_size
		//
		namespace detail {
			template<typename Tuple>
			struct tuple_size_default_impl
				: public sprout::detail::nil_base
			{};
			template<template<typename...> class TupleClass, typename... Ts>
			struct tuple_size_default_impl<TupleClass<Ts...> >
				: public sprout::integral_constant<std::size_t, sizeof...(Ts)>
			{};
			template<template<typename VT, VT...> class IntegerSequenceClass, typename T, T... Vs>
			struct tuple_size_default_impl<IntegerSequenceClass<T, Vs...> >
				: public sprout::integral_constant<std::size_t, sizeof...(Vs)>
			{};

#define SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(TYPE) \
			template<template<TYPE...> class IntegerSequenceClass, TYPE... Vs> \
			struct tuple_size_default_impl<IntegerSequenceClass<Vs...> > \
				: public sprout::integral_constant<std::size_t, sizeof...(Vs)> \
			{}

			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(bool);
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(char);
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(signed char);
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(unsigned char);
#if SPROUT_USE_UNICODE_LITERALS
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(char16_t);
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(char32_t);
#endif
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(wchar_t);
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(short);
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(unsigned short);
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(int);
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(unsigned int);
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(long);
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(unsigned long);
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(long long);
			SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(unsigned long long);

#undef SPROUT_TYPES_DETAIL_TUPLE_SIZE_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL

			template<typename Tuple, bool = sprout::has_value<sprout::tuples::tuple_size<Tuple> >::value>
			struct tuple_size_default;
			template<typename Tuple>
			struct tuple_size_default<Tuple, false>
				: public sprout::types::detail::tuple_size_default_impl<Tuple>
			{};
			template<typename Tuple>
			struct tuple_size_default<Tuple, true>
				: public sprout::tuples::tuple_size<Tuple>
			{};
		}	// namespace detail
		template<typename T>
		struct tuple_size
			: public sprout::types::detail::tuple_size_default<T>
		{};

		//
		// tuple_element
		//
		namespace detail {
			template<std::size_t I, typename Tuple>
			struct tuple_element_default_impl
				: public sprout::detail::nil_base
			{};
			template<std::size_t I, template<typename...> class TupleClass, typename... Ts>
			struct tuple_element_default_impl<I, TupleClass<Ts...> >
				: public std::tuple_element<I, sprout::types::type_tuple<Ts...> >
			{};
			template<std::size_t I, template<typename VT, VT...> class IntegerSequenceClass, typename T, T... Vs>
			struct tuple_element_default_impl<I, IntegerSequenceClass<T, Vs...> >
				: public std::tuple_element<I, sprout::types::type_tuple<sprout::integral_constant<T, Vs>...> >
			{};

#define SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(TYPE) \
			template<std::size_t I, template<TYPE...> class IntegerSequenceClass, TYPE... Vs> \
			struct tuple_element_default_impl<I, IntegerSequenceClass<Vs...> > \
				: public std::tuple_element<I, sprout::types::type_tuple<sprout::integral_constant<TYPE, Vs>...> > \
			{}

			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(bool);
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(char);
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(signed char);
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(unsigned char);
#if SPROUT_USE_UNICODE_LITERALS
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(char16_t);
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(char32_t);
#endif
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(wchar_t);
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(short);
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(unsigned short);
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(int);
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(unsigned int);
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(long);
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(unsigned long);
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(long long);
			SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL(unsigned long long);

#undef SPROUT_TYPES_DETAIL_TUPLE_ELEMENT_DEFAULT_IMPL_INTEGER_SEQUENCE_LIKE_DECL

			template<std::size_t I, typename Tuple, bool = sprout::has_type<sprout::tuples::tuple_element<I, Tuple> >::value>
			struct tuple_element_default;
			template<std::size_t I, typename Tuple>
			struct tuple_element_default<I, Tuple, false>
				: public sprout::types::detail::tuple_element_default_impl<I, Tuple>
			{};
			template<std::size_t I, typename Tuple>
			struct tuple_element_default<I, Tuple, true>
				: public sprout::tuples::tuple_element<I, Tuple>
			{};
		}	// namespace detail
		template<std::size_t I, typename T>
		struct tuple_element
			: public sprout::types::detail::tuple_element_default<I, T>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename T>
		using begin_t = typename sprout::types::begin<T>::type;
		template<typename T>
		using end_t = typename sprout::types::end<T>::type;

		template<std::size_t I, typename T>
		using tuple_element_t = typename sprout::types::tuple_element<I, T>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename Tuple>
		SPROUT_STATIC_CONSTEXPR std::size_t tuple_size_v = sprout::types::tuple_size<Tuple>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
	}	// namespace types
}	// namespace sprout

#include <sprout/type/type_tuple.hpp>

#endif	// #ifndef SPROUT_TYPE_TUPLE_HPP
