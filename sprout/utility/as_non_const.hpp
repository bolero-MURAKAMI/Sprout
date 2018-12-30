/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_AS_NON_CONST_HPP
#define SPROUT_UTILITY_AS_NON_CONST_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// as_non_const
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename std::conditional<
		std::is_lvalue_reference<T>::value,
		typename std::remove_const<typename std::remove_reference<T>::type>::type&,
		typename std::remove_const<typename std::remove_reference<T>::type>::type&&
	>::type
	as_non_const(T&& t) {
		typedef typename std::conditional<
			std::is_lvalue_reference<T>::value,
			typename std::remove_const<typename std::remove_reference<T>::type>::type&,
			typename std::remove_const<typename std::remove_reference<T>::type>::type&&
		>::type type;
		return const_cast<type>(t);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_AS_NON_CONST_HPP
