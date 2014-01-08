/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_UTILITY_EXCAHNGE_HPP
#define SPROUT_UTILITY_EXCAHNGE_HPP

#include <sprout/config.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/move.hpp>

namespace sprout {
	//
	// 20.2.3 exchange
	//
	template<typename T, typename U = T>
	inline SPROUT_CXX14_CONSTEXPR T
	exchange(T& obj, U&& new_val) {
		T old_val = sprout::move(obj);
		obj = sprout::forward<U>(new_val);
		return old_val;
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_UTILITY_EXCAHNGE_HPP
