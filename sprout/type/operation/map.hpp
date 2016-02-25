/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TYPE_OPERATION_MAP_HPP
#define SPROUT_TYPE_OPERATION_MAP_HPP

#include <sprout/config.hpp>
#include <sprout/type/apply.hpp>
#include <sprout/type/map_types.hpp>

namespace sprout {
	namespace types {
		//
		// map
		//
		template<typename Tuple, typename Op>
		struct map
			: public sprout::types::apply<sprout::types::map_types<Tuple>, Op>
		{};

#if SPROUT_USE_TEMPLATE_ALIASES
		template<typename Tuple, typename Op>
		using map_t = typename sprout::types::map<Tuple, Op>::type;
#endif	// #if SPROUT_USE_TEMPLATE_ALIASES
	}	// namespace types
}	// namespace sprout

#endif	// #ifndef SPROUT_TYPE_OPERATION_MAP_HPP
