/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_MEMSET_HPP
#define SPROUT_CSTRING_MEMSET_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/cxx14/fill.hpp>

namespace sprout {
	namespace detail {
		template<typename PtrIterator, typename T>
		inline SPROUT_CXX14_CONSTEXPR PtrIterator
		memset(PtrIterator s, T c, std::size_t n) {
			sprout::fill(s, s + n, c);
			return s;
		}
	}	// namespace detail

	// 7.21.6.1 The memset function
	//
	template<
		typename T,
		typename sprout::enabler_if<std::is_convertible<T, void*>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR void*
	memset(T s, int c, std::size_t n) {
		return sprout::detail::memset(static_cast<unsigned char*>(s), static_cast<unsigned char>(c), n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_MEMSET_HPP
