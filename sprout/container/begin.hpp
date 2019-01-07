/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_BEGIN_HPP
#define SPROUT_CONTAINER_BEGIN_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// begin
	//
	//	effect:
	//		sprout::container_range_traits<Container>::range_begin(cont)
	//		[default]
	//			ADL callable range_begin(cont) -> range_begin(cont)
	//			[default]
	//				Container is T[N] -> iterator(cont)
	//				otherwise, Container is not const
	//					&& sprout::is_const_iterator_cast_convertible<const_iterator, iterator>
	//					&& (callable sprout::as_const(cont).begin()
	//						|| ADL(without sprout) callable begin(sprout::as_const(cont))
	//						)
	//					-> sprout::const_iterator_cast<iterator>(sprout::begin(sprout::as_const(cont)))
	//				otherwise, callable cont.begin() -> cont.begin()
	//				otherwise, ADL(without sprout) callable begin(cont) -> begin(cont)
	//				otherwise -> std::begin(cont)
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	begin(Container& cont) {
		return sprout::container_range_traits<Container>::range_begin(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	begin(Container const& cont) {
		return sprout::container_range_traits<Container const>::range_begin(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
	begin(T (& arr)[N]) {
		return sprout::container_range_traits<T[N]>::range_begin(arr);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
	begin(T const (& arr)[N]) {
		return sprout::container_range_traits<T const[N]>::range_begin(arr);
	}

	//
	// cbegin
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	cbegin(Container const& cont) {
		return sprout::begin(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
	cbegin(T const (& arr)[N]) {
		return sprout::begin(arr);
	}
}	// namespace sprout

#include <sprout/container/container_range_traits.hpp>

#endif	// #ifndef SPROUT_CONTAINER_BEGIN_HPP
