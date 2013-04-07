#ifndef SPROUT_INDEX_TUPLE_UDL_HPP
#define SPROUT_INDEX_TUPLE_UDL_HPP

#include <sprout/config.hpp>
#include <sprout/index_tuple/index_tuple.hpp>

#if SPROUT_USE_USER_DEFINED_LITERALS

#include <type_traits>
#include <sprout/index_tuple/make_index_tuple.hpp>

namespace sprout {
	namespace detail {
		template<typename IntType, char... Chars>
		struct digits_to_int;
		template<typename IntType, char C>
		struct digits_to_int<IntType, C>
			: public std::integral_constant<IntType, IntType(C - 48)>
		{};
		template<typename IntType, char Head, char... Tail>
		struct digits_to_int<IntType, Head, Tail...>
			: public std::integral_constant<IntType, 10 * IntType(Head - 48) + sprout::detail::digits_to_int<IntType, Tail...>::value>
		{};
	}	// namespace detail

	//
	// indexes_result
	//
	template<char... Chars>
	struct indexes_result
		: public sprout::make_index_tuple<sprout::detail::digits_to_int<sprout::index_t, Chars...>::value>
	{};
	//
	// uindexes_result
	//
	template<char... Chars>
	struct uindexes_result
		: public sprout::make_uindex_tuple<sprout::detail::digits_to_int<sprout::uindex_t, Chars...>::value>
	{};

	namespace udl {
		//
		// _indexes
		//
		template<char... Chars>
		SPROUT_CONSTEXPR typename sprout::indexes_result<Chars...>::type
		operator "" _indexes() {
			return sprout::indexes_result<Chars...>::make();
		}

		//
		// _uindexes
		//
		template<char... Chars>
		SPROUT_CONSTEXPR typename sprout::uindexes_result<Chars...>::type
		operator "" _uindexes() {
			return sprout::uindexes_result<Chars...>::make();
		}
	}	// namespace udl

	using sprout::udl::operator "" _indexes;
	using sprout::udl::operator "" _uindexes;
}	// namespace sprout

#endif	// #if SPROUT_USE_USER_DEFINED_LITERALS

#endif	// #ifndef SPROUT_INDEX_TUPLE_UDL_HPP
