/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_DEFAULT_CONSTRUCT_HPP
#define SPROUT_TUPLE_DEFAULT_CONSTRUCT_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace tuples {
		//
		// default_construct_t
		// default_construct
		//
		struct default_construct_t {};
		SPROUT_STATIC_CONSTEXPR sprout::tuples::default_construct_t default_construct = {};
	}	// namespace tuples

	using sprout::tuples::default_construct_t;
	using sprout::tuples::default_construct;
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_DEFAULT_CONSTRUCT_HPP
