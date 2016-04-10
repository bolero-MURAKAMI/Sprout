/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_INDEX_OF_HPP
#define SPROUT_CONTAINER_INDEX_OF_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// index_of
	//
	//	effect:
	//		sprout::container_range_traits<Container>::range_index_of(cont, p)
	//		[default]
	//			ADL callable range_index_of(cont, p) -> range_index_of(cont, p)
	//			[default]
	//				Container is T[N] -> p - iterator(cont)
	//				callable cont.index_of(p) -> cont.index_of(p)
	//				otherwise -> sprout::distance(begin(cont), p)
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::size_type
	index_of(Container& cont, typename sprout::container_traits<Container>::iterator p) {
		return sprout::container_range_traits<Container>::range_index_of(cont, p);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
	index_of(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
		return sprout::container_range_traits<Container const>::range_index_of(cont, p);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::size_type
	index_of(T (& arr)[N], typename sprout::container_traits<T[N]>::iterator p) {
		return sprout::container_range_traits<T[N]>::range_index_of(arr, p);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::size_type
	index_of(T const (& arr)[N], typename sprout::container_traits<T const[N]>::iterator p) {
		return sprout::container_range_traits<T const[N]>::range_index_of(arr, p);
	}

	//
	// cindex_of
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
	cindex_of(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
		return sprout::index_of(cont, p);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::size_type
	cindex_of(T const (& arr)[N], typename sprout::container_traits<T const[N]>::iterator p) {
		return sprout::index_of(arr, p);
	}
}	// namespace sprout

#include <sprout/container/container_range_traits.hpp>

#endif	// #ifndef SPROUT_CONTAINER_INDEX_OF_HPP
