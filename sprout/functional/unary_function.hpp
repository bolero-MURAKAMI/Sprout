/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_FUNCTIONAL_UNARY_FUNCTION_HPP
#define SPROUT_FUNCTIONAL_UNARY_FUNCTION_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// unary_function
	//
	template<typename Arg, typename Result>
	struct unary_function {
	public:
		typedef Arg argument_type;
		typedef Result result_type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_FUNCTIONAL_UNARY_FUNCTION_HPP
