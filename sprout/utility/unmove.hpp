/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_UNMOVE_HPP
#define SPROUT_UTILITY_UNMOVE_HPP

#include <type_traits>
#include <sprout/config.hpp>

namespace sprout {
	//
	// unmove
	//
	template<typename T>
	inline SPROUT_CONSTEXPR typename std::remove_reference<T>::type&
	unmove(T&& x) SPROUT_NOEXCEPT {
		return static_cast<typename std::remove_reference<T>::type&>(x);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_UNMOVE_HPP
