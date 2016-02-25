/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_PACKER_HPP
#define SPROUT_TYPE_PACKER_HPP

#include <tuple>
#include <sprout/config.hpp>
#include <sprout/type/type_tuple.hpp>
#include <sprout/type/tuple.hpp>

namespace sprout {
	namespace types {
		//
		// packer
		//
#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename... Types>
		using packer = sprout::types::type_tuple<Types...>;
#else	// #if SPROUT_USE_TEMPLATE_ALIASES
		template<typename... Types>
		struct packer
			: public sprout::types::type_tuple<Types...>
		{};
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types

	using sprout::types::packer;
}	// namespace sprout

#if !SPROUT_USE_TEMPLATE_ALIASES

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<typename... Types>
	struct tuple_size<sprout::types::packer<Types...> >
		: public std::tuple_size<sprout::types::type_tuple<Types...> >
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename... Types>
	struct tuple_element<I, sprout::types::packer<Types...> >
		: public sprout::types::tuple_element<I, sprout::types::packer<Types...> >
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

namespace sprout {
	//
	// tuple_get
	//
	template<std::size_t I, typename... Types>
	inline SPROUT_CONSTEXPR typename std::tuple_element<I, sprout::types::packer<Types...> >::type
	tuple_get(sprout::types::packer<Types...>) SPROUT_NOEXCEPT {
		static_assert(I < sizeof...(Values), "tuple_get: index out of range");
		typedef typename std::tuple_element<I, sprout::types::packer<Types...> >::type type;
		return type();
	}
}	// namespace sprout

#endif	// #if !SPROUT_USE_TEMPLATE_ALIASES

#include <sprout/index_tuple/metafunction.hpp>
#include <sprout/type/algorithm/contains.hpp>
#include <sprout/tpp/algorithm/all_of.hpp>

namespace sprout {
	namespace types {
		//
		// is_contained_in
		//
		template<typename T, typename... Types>
		struct is_contained_in
			: public sprout::types::contains<sprout::types::type_tuple<Types...>, T>
		{};

		//
		// contains_types
		//
		namespace detail {
			template<typename T, typename U, typename IndexTuple>
			struct contains_types_impl;
			template<typename T, typename U, sprout::index_t... Indexes>
			struct contains_types_impl<T, U, sprout::index_tuple<Indexes...> >
				: public sprout::tpp::all_of<sprout::types::is_contained_in<typename sprout::types::tuple_element<Indexes, U>::type, T>...>
			{};
		}	// namespace detail
		template<typename T, typename U>
		struct contains_types
			: public sprout::types::detail::contains_types_impl<T, U, typename sprout::make_index_tuple<sprout::types::tuple_size<U>::value>::type>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename T, typename... Types>
		using is_contained_in_t = typename sprout::types::is_contained_in<T, Types...>::type;

		template<typename T, typename U>
		using contains_types_t = typename sprout::types::contains_types<T, U>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
		template<typename T, typename... Types>
		SPROUT_STATIC_CONSTEXPR bool is_contained_in_v = sprout::types::is_contained_in<T, Types...>::value;

		template<typename T, typename U>
		SPROUT_STATIC_CONSTEXPR bool contains_types_v = sprout::types::contains_types<T, U>::value;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES

	}	// namespace types

	using sprout::types::is_contained_in;
	using sprout::types::contains_types;

#if SPROUT_USE_TEMPLATE_ALIASES
	using sprout::types::is_contained_in_t;
	using sprout::types::contains_types_t;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES

#if SPROUT_USE_VARIABLE_TEMPLATES
	using sprout::types::is_contained_in_v;
	using sprout::types::contains_types_v;
#endif	// #if SPROUT_USE_VARIABLE_TEMPLATES
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_PACKER_HPP
