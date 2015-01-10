/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_STRCOLL_HPP
#define SPROUT_CSTRING_STRCOLL_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/type_traits/is_char_type.hpp>
#include <sprout/cstring/strcmp.hpp>

namespace sprout {

	// 7.21.4.3 strcoll ä÷êî
	//
	//	recursion depth:
	//		O(log(N1+N2))
	//
	inline SPROUT_CONSTEXPR int
	strcoll(char const* s1, char const* s2) {
		return sprout::strcmp(s1, s2);
	}

	template<typename Elem>
	inline SPROUT_CONSTEXPR typename std::enable_if<
		sprout::is_char_type<Elem>::value,
		int
	>::type
	strcoll(Elem* s1, Elem* s2) {
		return sprout::strcmp(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRCOLL_HPP
