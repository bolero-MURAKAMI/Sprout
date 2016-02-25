/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CSTRING_MEMMOVE_HPP
#define SPROUT_CSTRING_MEMMOVE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/type_traits/enabler_if.hpp>
#include <sprout/algorithm/cxx14/copy_backward.hpp>

namespace sprout {
	namespace detail {
		template<typename PtrIterator, typename ConstPtrIterator>
		inline SPROUT_CXX14_CONSTEXPR PtrIterator
		memmove(PtrIterator s1, ConstPtrIterator s2, std::size_t n) {
			sprout::copy_backward(s2, s2 + n, s1);
			return s1;
		}
	}	// namespace detail

	// 7.21.2.2 The memmove function
	//
	template<
		typename T, typename CT,
		typename sprout::enabler_if<std::is_convertible<T, void*>::value && std::is_convertible<CT, void const*>::value>::type = sprout::enabler
	>
	inline SPROUT_CXX14_CONSTEXPR void*
	memmove(T s1, CT s2, std::size_t n) {
		return sprout::detail::memmove(static_cast<unsigned char*>(s1), static_cast<unsigned char const*>(s2), n);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CSTRING_MEMMOVE_HPP
