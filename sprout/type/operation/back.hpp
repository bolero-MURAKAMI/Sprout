/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_BACK_HPP
#define SPROUT_TYPE_OPERATION_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/type/operation/size.hpp>
#include <sprout/type/operation/at.hpp>

namespace sprout {
	namespace types {
		//
		// back
		//
		template<typename Tuple>
		struct back
			: public sprout::types::at<Tuple, (sprout::types::size<Tuple>::value - 1)>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple>
		using back_t = typename sprout::types::back<Tuple>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_BACK_HPP
