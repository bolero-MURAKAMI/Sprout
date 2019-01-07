/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_STRCPY_HPP
#define SPROUT_CSTRING_STRCPY_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename OutputNullTerminatedIterator, typename NullTerminatedIterator>
		inline SPROUT_CXX14_CONSTEXPR OutputNullTerminatedIterator
		strcpy(OutputNullTerminatedIterator s1, NullTerminatedIterator s2) {
			OutputNullTerminatedIterator result = s1;
			while ((*s1++ = *s2++))
				;
			return result;
		}
	}	// namespace detail

	// 7.21.2.3 The strcpy function
	//
	inline SPROUT_CXX14_CONSTEXPR char*
	strcpy(char* s1, char const* s2) {
		return sprout::detail::strcpy(s1, s2);
	}

	template<typename Elem>
	inline SPROUT_CXX14_CONSTEXPR Elem*
	strcpy(Elem* s1, Elem const* s2) {
		return sprout::detail::strcpy(s1, s2);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRCPY_HPP
