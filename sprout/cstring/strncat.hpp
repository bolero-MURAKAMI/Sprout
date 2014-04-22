/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_STRNCAT_HPP
#define SPROUT_CSTRING_STRNCAT_HPP

#include <iterator>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename OutputCStrIterator, typename CStrIterator>
		inline SPROUT_CXX14_CONSTEXPR OutputCStrIterator
		strncat(OutputCStrIterator s1, CStrIterator s2, std::size_t n) {
			typedef typename std::iterator_traits<OutputCStrIterator>::value_type value_type;
			OutputCStrIterator result = s1;
			while (*s1) {
				++s1;
			}
			while (n) {
				--n;
				if (!(*s1++ = *s2++)) {
					break;
				}
			}
			*s1 = value_type();
			return result;
		}
	}	// namespace detail

	// 7.21.3.2 The strncat function
	//
	inline SPROUT_CXX14_CONSTEXPR char*
	strncat(char* s1, char const* s2, std::size_t n) {
		return sprout::detail::strncat(s1, s2, n);
	}

	template<typename Elem>
	inline SPROUT_CXX14_CONSTEXPR Elem*
	strncat(Elem* s1, Elem const* s2, std::size_t n) {
		return sprout::detail::strncat(s1, s2, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRNCAT_HPP
