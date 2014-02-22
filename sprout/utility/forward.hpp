/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_FORWARD_HPP
#define SPROUT_UTILITY_FORWARD_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// forward
	//
	template<typename T>
	inline SPROUT_CONSTEXPR T&&
	forward(typename std::remove_reference<T>::type& t) SPROUT_NOEXCEPT {
		return static_cast<T&&>(t);
	}
	template<typename T>
	inline SPROUT_CONSTEXPR T&&
	forward(typename std::remove_reference<T>::type&&) SPROUT_NOEXCEPT SPROUT_DELETED_FUNCTION_DECL
}	// namespace sprout

//
// SPROUT_FORWARD
//
#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
#	define SPROUT_FORWARD(TYPE, VALUE) \
		static_cast<decltype(::sprout::forward<TYPE>(VALUE))>(VALUE)
#else
#	define SPROUT_FORWARD(TYPE, VALUE) \
		::sprout::forward<TYPE>(VALUE)
#endif

#endif	// #ifndef SPROUT_UTILITY_FORWARD_HPP
