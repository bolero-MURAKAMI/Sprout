/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_STRNCPY_HPP
#define SPROUT_CSTRING_STRNCPY_HPP

#include <iterator>
#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		template<typename OutputNullTerminatedIterator, typename NullTerminatedIterator>
		inline SPROUT_CXX14_CONSTEXPR OutputNullTerminatedIterator
		strncpy(OutputNullTerminatedIterator s1, NullTerminatedIterator s2, std::size_t n) {
			typedef typename std::iterator_traits<OutputNullTerminatedIterator>::value_type value_type;
			OutputNullTerminatedIterator result = s1;
			while (n) {
				--n;
				if (!(*s1++ = *s2++)) {
					break;
				}
			}
			while (n) {
				--n;
				*s1++ = value_type();
			}
			return result;
		}
	}	// namespace detail

	// 7.21.2.4 The strncpy function
	//
	inline SPROUT_CXX14_CONSTEXPR char*
	strncpy(char* s1, char const* s2, std::size_t n) {
		return sprout::detail::strncpy(s1, s2, n);
	}

	template<typename Elem>
	inline SPROUT_CXX14_CONSTEXPR Elem*
	strncpy(Elem* s1, Elem const* s2, std::size_t n) {
		return sprout::detail::strncpy(s1, s2, n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_STRNCPY_HPP
