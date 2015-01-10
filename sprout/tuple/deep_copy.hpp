/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_TUPLE_DEEP_COPY_HPP
#define SPROUT_TUPLE_DEEP_COPY_HPP

#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/tuple/traits.hpp>
#include <sprout/utility/forward.hpp>

namespace sprout {
	namespace tuples {
		//
		// deep_copy
		//
		template<typename Tuple>
		inline SPROUT_CONSTEXPR typename sprout::tuples::tuple_construct_traits<
			typename std::remove_reference<Tuple>::type
		>::copied_type
		deep_copy(Tuple&& tup) {
			typedef typename std::remove_reference<Tuple>::type tuple_type;
			return sprout::tuples::tuple_construct_traits<tuple_type>::deep_copy(SPROUT_FORWARD(Tuple, tup));
		}
	}	// namespace tuples
}	// namespace sprout

#endif	// #ifndef SPROUT_TUPLE_DEEP_COPY_HPP
