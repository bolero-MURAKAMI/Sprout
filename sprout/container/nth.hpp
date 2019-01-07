/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_NTH_HPP
#define SPROUT_CONTAINER_NTH_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// nth
	//
	//	effect:
	//		sprout::container_range_traits<Container>::range_nth(cont, i)
	//		[default]
	//			ADL callable range_nth(cont, i) -> range_nth(cont, i)
	//			[default]
	//				Container is T[N] -> iterator(cont) + i
	//				otherwise, Container is not const
	//					&& sprout::is_const_iterator_cast_convertible<const_iterator, iterator>
	//					&& (callable sprout::as_const(cont).nth(i)
	//						|| callable sprout::as_const(cont).begin()
	//						|| ADL(without sprout) callable begin(sprout::as_const(cont))
	//						)
	//					-> sprout::const_iterator_cast<iterator>(sprout::nth(sprout::as_const(cont), i))
	//				otherwise, callable cont.nth(i) -> cont.nth(i)
	//				otherwise -> sprout::next(sprout::begin(cont), i)
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	nth(Container& cont, typename sprout::container_traits<Container>::size_type i) {
		return sprout::container_range_traits<Container>::range_nth(cont, i);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	nth(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		return sprout::container_range_traits<Container const>::range_nth(cont, i);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
	nth(T (& arr)[N], typename sprout::container_traits<T[N]>::size_type i) {
		return sprout::container_range_traits<T[N]>::range_nth(arr, i);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
	nth(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
		return sprout::container_range_traits<T const[N]>::range_nth(arr, i);
	}

	//
	// cnth
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	cnth(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		return sprout::nth(cont, i);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
	cnth(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
		return sprout::nth(arr, i);
	}
}	// namespace sprout

#include <sprout/container/container_range_traits.hpp>

#endif	// #ifndef SPROUT_CONTAINER_NTH_HPP
