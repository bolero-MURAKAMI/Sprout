/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_FRONT_HPP
#define SPROUT_TYPE_OPERATION_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/type/operation/at.hpp>

namespace sprout {
	namespace types {
		//
		// front
		//
		template<typename Tuple>
		struct front
			: public sprout::types::at<Tuple, 0>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple>
		using front_t = typename sprout::types::front<Tuple>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_FRONT_HPP
