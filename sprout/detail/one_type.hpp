/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DETAIL_ONE_TYPE_HPP
#define SPROUT_DETAIL_ONE_TYPE_HPP

#include <sprout/config.hpp>

namespace sprout {
	namespace detail {
		//
		// one_type
		//
		typedef char one_type;

		//
		// not_one_type
		//
		struct not_one_type {
		public:
		   char padding[8];
		};
	}	// namespace detail
}	// namespace sprout

#endif	// #ifndef SPROUT_DETAIL_ONE_TYPE_HPP
