/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_DIGITS_TO_INT_HPP
#define SPROUT_DETAIL_DIGITS_TO_INT_HPP

#include <sprout/config.hpp>
#include <sprout/type_traits/integral_constant.hpp>

namespace sprout {
	namespace detail {
		template<typename IntType, char... Chars>
		struct digits_to_int;
		template<typename IntType, char C>
		struct digits_to_int<IntType, C>
			: public sprout::integral_constant<IntType, IntType(C - 48)>
		{};
		template<typename IntType, char Head, char... Tail>
		struct digits_to_int<IntType, Head, Tail...>
			: public sprout::integral_constant<IntType, 10 * IntType(Head - 48) + sprout::detail::digits_to_int<IntType, Tail...>::value>
		{};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_DIGITS_TO_INT_HPP
