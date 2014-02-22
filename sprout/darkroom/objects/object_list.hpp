/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_DARKROOM_OBJECTS_OBJECT_LIST_HPP
#define SPROUT_DARKROOM_OBJECTS_OBJECT_LIST_HPP

#include <sprout/config.hpp>
#include <sprout/tuple/tuple/make_tuple.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace darkroom {
		namespace objects {
			//
			// make_object_list
			//
			template<typename... Objects>
			inline SPROUT_CONSTEXPR auto
			make_object_list(Objects&&... objs)
			-> decltype(sprout::make_tuple(SPROUT_FORWARD(Objects, objs)...))
			{
				return sprout::make_tuple(SPROUT_FORWARD(Objects, objs)...);
			}
		}	// namespace objects
	}	// namespace darkroom
}	// namespace sprout

#endif	// #ifndef SPROUT_DARKROOM_OBJECTS_OBJECT_LIST_HPP
