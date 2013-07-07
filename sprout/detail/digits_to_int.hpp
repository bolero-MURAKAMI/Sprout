#ifndef SPROUT_DETAIL_DIGITS_TO_INT_HPP
#define SPROUT_DETAIL_DIGITS_TO_INT_HPP

#include <type_traits>
#include <sprout/config.hpp>

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
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_DIGITS_TO_INT_HPP
