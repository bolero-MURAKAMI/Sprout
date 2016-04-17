/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef TESTSPR_UTILITY_HPP
#define TESTSPR_UTILITY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/as_non_const.hpp>

namespace testspr {
	//
	// as_const
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename std::conditional<
		std::is_lvalue_reference<T>::value,
		typename std::remove_reference<T>::type const&,
		typename std::remove_reference<T>::type const&&
	>::type
	as_const(T&& t) {
		return SPROUT_FORWARD(T, t);
	}

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
}	// namespace testspr

#endif	// #ifndef TESTSPR_UTILITY_HPP
