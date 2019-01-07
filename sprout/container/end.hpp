/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_END_HPP
#define SPROUT_CONTAINER_END_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// end
	//
	//	effect:
	//		sprout::container_range_traits<Container>::range_end(cont)
	//		[default]
	//			ADL callable range_end(cont) -> range_end(cont)
	//			[default]
	//				Container is T[N] -> iterator(cont)
	//				otherwise, Container is not const
	//					&& sprout::is_const_iterator_cast_convertible<const_iterator, iterator>
	//					&& (callable sprout::as_const(cont).end()
	//						|| ADL(without sprout) callable end(sprout::as_const(cont))
	//						)
	//					-> sprout::const_iterator_cast<iterator>(sprout::end(sprout::as_const(cont)))
	//				otherwise, callable cont.end() -> cont.end()
	//				otherwise, ADL(without sprout) callable end(cont) -> end(cont)
	//				otherwise -> std::end(cont)
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	end(Container& cont) {
		return sprout::container_range_traits<Container>::range_end(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	end(Container const& cont) {
		return sprout::container_range_traits<Container const>::range_end(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
	end(T (& arr)[N]) {
		return sprout::container_range_traits<T[N]>::range_end(arr);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
	end(T const (& arr)[N]) {
		return sprout::container_range_traits<T const[N]>::range_end(arr);
	}

	//
	// cend
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	cend(Container const& cont) {
		return sprout::end(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
	cend(T const (& arr)[N]) {
		return sprout::end(arr);
	}
}	// namespace sprout

#include <sprout/container/container_range_traits.hpp>

#endif	// #ifndef SPROUT_CONTAINER_END_HPP
