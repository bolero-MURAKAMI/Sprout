/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CTIME_DIFFTIME_HPP
#define SPROUT_CTIME_DIFFTIME_HPP

#include <ctime>
#include <sprout/config.hpp>

namespace sprout {
	//
	// 7.23.2.2 The difftime function
	//
	inline SPROUT_CONSTEXPR double
	difftime(std::time_t time1, std::time_t time0) {
		return static_cast<double>(time1) - static_cast<double>(time0);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CTIME_DIFFTIME_HPP
