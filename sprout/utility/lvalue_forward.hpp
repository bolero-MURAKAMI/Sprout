/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_LVALUE_FORWARD_HPP
#define SPROUT_UTILITY_LVALUE_FORWARD_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/as_lvalue.hpp>
#include <sprout/type_traits/lvalue_reference.hpp>

namespace sprout {
	//
	// lvalue_forward
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::lvalue_reference<T>::type
	lvalue_forward(typename std::remove_reference<T>::type& t) {
		return sprout::as_lvalue(SPROUT_FORWARD(T, t));
	}
	template<typename T>
	inline SPROUT_CONSTEXPR typename sprout::lvalue_reference<T>::type
	lvalue_forward(typename std::remove_reference<T>::type&&) SPROUT_DELETED_FUNCTION_DECL
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_LVALUE_FORWARD_HPP
