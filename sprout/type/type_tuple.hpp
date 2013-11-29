/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_TYPE_TUPLE_HPP
#define SPROUT_TYPE_TYPE_TUPLE_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/iterator.hpp>
#include <sprout/type/iterator/index_iterator.hpp>
#include <sprout/type/rebind_types.hpp>
#include <sprout/type_traits/integral_constant.hpp>
#include <sprout/type_traits/identity.hpp>

namespace sprout {
	namespace types {
		//
		// type_tuple
		//
		template<typename... Types>
		struct type_tuple {
		public:
			typedef type_tuple type;
			typedef sprout::types::index_iterator<type_tuple, 0> begin;
			typedef sprout::types::index_iterator<type_tuple, sizeof...(Types)> end;
		public:
			SPROUT_STATIC_CONSTEXPR std::size_t static_size = sizeof...(Types);
		};
		template<typename... Types>
		SPROUT_CONSTEXPR_OR_CONST std::size_t sprout::types::type_tuple<Types...>::static_size;

		//
		// rebind_types
		//
		template<typename... Ts>
		struct rebind_types<sprout::types::type_tuple<Ts...> > {
		public:
			template<typename... Types>
			struct apply {
			public:
				typedef sprout::types::type_tuple<Types...> type;
			};
		};

		namespace detail {
			template<typename T>
			struct tuple_head;
			template<typename Head, typename... Tail>
			struct tuple_head<sprout::types::type_tuple<Head, Tail...> >
				: public sprout::identity<Head>
			{};

			template<std::size_t I, std::size_t N, typename T, typename Enable = void>
			struct tuple_skip;
			template<std::size_t I, std::size_t N, typename Head, typename... Tail>
			struct tuple_skip<
				I, N, sprout::types::type_tuple<Head, Tail...>,
				typename std::enable_if<(I == 0)>::type
			>
				: public sprout::identity<sprout::types::type_tuple<Head, Tail...> >
			{};
			template<std::size_t I, std::size_t N, typename Head, typename... Tail>
			struct tuple_skip<
				I, N, sprout::types::type_tuple<Head, Tail...>,
				typename std::enable_if<(I != 0 && I < N / 2)>::type
			>
				: public sprout::types::detail::tuple_skip<
					I - 1, N / 2 - 1,
					sprout::types::type_tuple<Tail...>
				>
			{};
			template<std::size_t I, std::size_t N, typename Head, typename... Tail>
			struct tuple_skip<
				I, N, sprout::types::type_tuple<Head, Tail...>,
				typename std::enable_if<(I != 0 && I >= N / 2)>::type
			>
				: public sprout::types::detail::tuple_skip<
					I - N / 2, N - N / 2,
					typename sprout::types::detail::tuple_skip<N / 2 - 1, N / 2, sprout::types::type_tuple<Tail...> >::type
				>
			{};
		}	// namespace detail
	}	// namespace types

	using sprout::types::type_tuple;
	using sprout::types::rebind_types;
}	// namespace sprout

namespace std {
#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wmismatched-tags"
#endif
	//
	// tuple_size
	//
	template<typename... Types>
	struct tuple_size<sprout::types::type_tuple<Types...> >
		: public sprout::integral_constant<std::size_t, sizeof...(Types)>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename... Types>
	struct tuple_element<I, sprout::types::type_tuple<Types...> >
		: public sprout::types::detail::tuple_head<
			typename sprout::types::detail::tuple_skip<I, sizeof...(Types), sprout::types::type_tuple<Types...> >::type
		>
	{};
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
}	// namespace std

#endif	// #ifndef SPROUT_TYPE_TYPE_TUPLE_HPP
