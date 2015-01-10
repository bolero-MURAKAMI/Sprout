/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_FORWARD_HPP
#define SPROUT_UTILITY_FORWARD_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/preprocessor/config.hpp>
#include <sprout/preprocessor/cat.hpp>
#include <sprout/preprocessor/variadic/size.hpp>

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

#if defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC) || defined(__ECC)
#	define SPROUT_FORWARD_2(TYPE, VAR) \
		static_cast<decltype(::sprout::forward<TYPE>(VAR))>(VAR)
#else
#	define SPROUT_FORWARD_2(TYPE, VAR) \
		::sprout::forward<TYPE>(VAR)
#endif

//
// SPROUT_AUTO_FORWARD
//
#define SPROUT_AUTO_FORWARD(VAR) SPROUT_FORWARD_2(decltype(VAR), VAR)

//
// SPROUT_FORWARD
//
#if SPROUT_PP_VARIADICS
#	define SPROUT_FORWARD_1(VAR) \
		SPROUT_AUTO_FORWARD(VAR)
#	define SPROUT_FORWARD(...) \
		SPROUT_PP_CAT(SPROUT_FORWARD_, SPROUT_PP_VARIADIC_SIZE(__VA_ARGS__))(__VA_ARGS__)
#else
#	define SPROUT_FORWARD(TYPE, VAR) \
		SPROUT_FORWARD_2(TYPE, VAR)
#endif

#endif	// #ifndef SPROUT_UTILITY_FORWARD_HPP
