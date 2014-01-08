/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_MAKE_HPP
#define SPROUT_TUPLE_MAKE_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace tuples {
		//
		// make
		//
		template<typename Tuple, typename... Args>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_construct_traits<Tuple>::copied_type
		make(Args&&... args) {
			return sprout::tuples::tuple_construct_traits<Tuple>::make(
				sprout::forward<Args>(args)...
				);
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_MAKE_HPP
