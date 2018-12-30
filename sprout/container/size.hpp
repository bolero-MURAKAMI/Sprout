/*=============================================================================
  Copyright (c) 2011-2018 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_SIZE_HPP
#define SPROUT_CONTAINER_SIZE_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// size
	//
	//	effect:
	//		sprout::container_range_traits<Container>::range_size(cont)
	//		[default]
	//			ADL callable range_size(cont) -> range_size(cont)
	//			[default]
	//				Container is T[N] -> N
	//				otherwise, callable cont.size() -> cont.size()
	//				otherwise -> distance(begin(cont), end(cont))
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
	size(Container const& cont) {
		return sprout::container_range_traits<Container const>::range_size(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::size_type
	size(T const (& arr)[N]) {
		return sprout::container_range_traits<T const[N]>::range_size(arr);
	}
}	// namespace sprout

#include <sprout/container/container_range_traits.hpp>

#endif	// #ifndef SPROUT_CONTAINER_SIZE_HPP
