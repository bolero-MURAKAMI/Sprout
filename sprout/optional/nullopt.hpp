/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_OPTIONAL_NULLOPT_HPP
#define SPROUT_OPTIONAL_NULLOPT_HPP

#include <sprout/config.hpp>
#include <sprout/none.hpp>

namespace sprout {
	//
	// nullopt_t
	// nullopt
	//
	typedef sprout::none_t nullopt_t;
	namespace {
		SPROUT_STATIC_CONSTEXPR nullopt_t nullopt{};
	}	// anonymous-namespace
}	// namespace sprout

#endif	// #ifndef SPROUT_OPTIONAL_NULLOPT_HPP
