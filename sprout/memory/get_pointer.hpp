/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_MEMORY_GET_POINTER_HPP
#define SPROUT_MEMORY_GET_POINTER_HPP

#include <memory>
#include <sprout/config.hpp>
#include <sprout/detail/predef.hpp>

namespace sprout {
	//
	// get_pointer
	//
	template<typename T>
	inline SPROUT_CONSTEXPR T*
	get_pointer(T* p) SPROUT_NOEXCEPT {
		return p;
	}

#if !SPROUT_CLANG_OR_LATER(5, 0, 0) || (_LIBCPP_STD_VER <= 14 || defined(_LIBCPP_ENABLE_CXX17_REMOVED_AUTO_PTR))
	template<typename T>
	inline SPROUT_NON_CONSTEXPR T*
	get_pointer(std::auto_ptr<T> const& p) SPROUT_NOEXCEPT {
		return p.get();
	}
#endif

#if !defined(SPROUT_NO_CXX11_SMART_PTR)
	template<typename T>
	inline SPROUT_NON_CONSTEXPR T*
	get_pointer(std::unique_ptr<T> const& p) SPROUT_NOEXCEPT {
		return p.get();
	}

	template<typename T>
	inline SPROUT_NON_CONSTEXPR T*
	get_pointer(std::shared_ptr<T> const& p) SPROUT_NOEXCEPT {
		return p.get();
	}
#endif
}	// namespace sprout


#endif	// #ifndef SPROUT_MEMORY_GET_POINTER_HPP
