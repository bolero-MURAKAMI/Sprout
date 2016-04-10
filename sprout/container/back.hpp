/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_BACK_HPP
#define SPROUT_CONTAINER_BACK_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// back
	//
	//	effect:
	//		sprout::container_range_traits<Container>::range_back(cont)
	//		[default]
	//			ADL callable range_back(cont) -> range_back(cont)
	//			[default]
	//				Container is T[N] -> cont[N - 1]
	//				callable cont.back() -> cont.back()
	//				otherwise -> *sprout::next(sprout::begin(cont), sprout::size(cont) - 1)
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	back(Container& cont) {
		return sprout::container_range_traits<Container>::range_back(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	back(Container const& cont) {
		return sprout::container_range_traits<Container const>::range_back(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
	back(T (& arr)[N]) {
		return sprout::container_range_traits<T[N]>::range_back(arr);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
	back(T const (& arr)[N]) {
		return sprout::container_range_traits<T const[N]>::range_back(arr);
	}

	//
	// cback
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	cback(Container const& cont) {
		return sprout::back(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
	cback(T const (& arr)[N]) {
		return sprout::back(arr);
	}
}	// namespace sprout

#include <sprout/container/container_range_traits.hpp>

#endif	// #ifndef SPROUT_CONTAINER_BACK_HPP
