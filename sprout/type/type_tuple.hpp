#ifndef SPROUT_TYPE_TYPE_TUPLE_HPP
#define SPROUT_TYPE_TYPE_TUPLE_HPP

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type/tuple.hpp>
#include <sprout/type/iterator.hpp>
#include <sprout/type/iterator/index_iterator.hpp>

namespace sprout {
	namespace types {
		//
		// type_tuple
		//
		template<typename... Types>
		struct type_tuple {
		public:
			typedef sprout::types::index_iterator<type_tuple, 0> begin;
			typedef sprout::types::index_iterator<type_tuple, sizeof...(Types)> end;
		};

		namespace detail {
			template<std::size_t I, typename T>
			struct tuple_element_impl;
			template<typename Head, typename... Tail>
			struct tuple_element_impl<0, sprout::types::type_tuple<Head, Tail...> > {
			public:
				typedef Head type;
			};
			template<std::size_t I, typename Head, typename... Tail>
			struct tuple_element_impl<I, sprout::types::type_tuple<Head, Tail...> >
				: public sprout::types::detail::tuple_element_impl<I - 1, sprout::types::type_tuple<Tail...> >
			{};
		}	// namespace detail
	}	// namespace types

	using sprout::types::type_tuple;
}	// namespace sprout

namespace std {
	//
	// tuple_size
	//
	template<typename... Types>
	struct tuple_size<sprout::types::type_tuple<Types...> >
		: public std::integral_constant<std::size_t, sizeof...(Types)>
	{};

	//
	// tuple_element
	//
	template<std::size_t I, typename... Types>
	struct tuple_element<I, sprout::types::type_tuple<Types...> >
		: public sprout::types::detail::tuple_element_impl<I, sprout::types::type_tuple<Types...> >
	{};
}	// namespace std

#endif	// #ifndef SPROUT_TYPE_TYPE_TUPLE_HPP
