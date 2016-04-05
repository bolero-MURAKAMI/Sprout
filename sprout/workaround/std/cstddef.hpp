/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_WORKAROUND_STD_CSTDDEF_HPP
#define SPROUT_WORKAROUND_STD_CSTDDEF_HPP

#include <sprout/config.hpp>
#include <sprout/detail/predef.hpp>

#if defined(__clang__) && defined(__GLIBCXX__)
#	if SPROUT_CLANG_EARLIER(3, 4, 2) && (__GLIBCXX__ >= 20140422)
#		include <stddef.h>
#
#		if defined(__STDDEF_H)
struct max_align_t {
	long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
	long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
};
#		endif
#	endif
#endif

#include <cstddef>

#endif	// #ifndef SPROUT_WORKAROUND_STD_CSTDDEF_HPP
