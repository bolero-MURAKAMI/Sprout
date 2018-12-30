/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_EMPTY_HPP
#define SPROUT_CONTAINER_EMPTY_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// empty
	//
	//	effect:
	//		sprout::container_range_traits<Container>::range_empty(cont)
	//		[default]
	//			ADL callable range_empty(cont) -> range_empty(cont)
	//			[default]
	//				Container is T[N] -> false
	//				otherwise, callable cont.empty() -> cont.empty()
	//				otherwise -> sprout::size(cont) == 0
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	empty(Container const& cont) {
		return sprout::container_range_traits<Container const>::range_empty(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	empty(T const (& arr)[N]) {
		return sprout::container_range_traits<T const[N]>::range_empty(arr);
	}
}	// namespace sprout

#include <sprout/container/container_range_traits.hpp>

#endif	// #ifndef SPROUT_CONTAINER_EMPTY_HPP
