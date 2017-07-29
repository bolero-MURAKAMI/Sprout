/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_VARIANT_STATIC_VISITOR_HPP
#define SPROUT_VARIANT_STATIC_VISITOR_HPP

#include <sprout/config.hpp>

namespace sprout {
	//
	// static_visitor
	//
	template<typename R = void>
	class static_visitor {
	public:
		typedef R result_type;
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_VARIANT_STATIC_VISITOR_HPP
