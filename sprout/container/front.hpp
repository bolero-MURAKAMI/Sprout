/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_FRONT_HPP
#define SPROUT_CONTAINER_FRONT_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// front
	//
	//	effect:
	//		sprout::container_range_traits<Container>::range_front(cont)
	//		[default]
	//			ADL callable range_front(cont) -> range_front(cont)
	//			[default]
	//				Container is T[N] -> cont[0]
	//				otherwise, Container is not const
	//					&& sprout::is_const_reference_cast_convertible<const_reference, reference>
	//					&& (callable sprout::as_const(cont).front()
	//						|| callable sprout::as_const(cont).begin()
	//						|| ADL(without sprout) callable begin(sprout::as_const(cont))
	//						)
	//					-> sprout::const_reference_cast<reference>(sprout::front(sprout::as_const(cont)))
	//				otherwise, callable cont.front() -> cont.front()
	//				otherwise -> *sprout::begin(cont)
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	front(Container& cont) {
		return sprout::container_range_traits<Container>::range_front(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	front(Container const& cont) {
		return sprout::container_range_traits<Container const>::range_front(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
	front(T (& arr)[N]) {
		return sprout::container_range_traits<T[N]>::range_front(arr);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
	front(T const (& arr)[N]) {
		return sprout::container_range_traits<T const[N]>::range_front(arr);
	}

	//
	// cfront
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	cfront(Container const& cont) {
		return sprout::front(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
	cfront(T const (& arr)[N]) {
		return sprout::front(arr);
	}
}	// namespace sprout

#include <sprout/container/container_range_traits.hpp>

#endif	// #ifndef SPROUT_CONTAINER_FRONT_HPP
