/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_BINARY_FUNCTION_HPP
#define SPROUT_FUNCTIONAL_BINARY_FUNCTION_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// binary_function
	//
	template<typename Arg1, typename Arg2, typename Result>
	struct binary_function {
	public:
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_BINARY_FUNCTION_HPP
