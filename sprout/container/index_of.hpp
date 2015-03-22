/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
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
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_index_of(...);
}	// namespace sprout_adl

namespace sprout {
	namespace container_detail {
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::size_type
		range_index_of(Container& cont, typename sprout::container_traits<Container>::iterator p) {
			return sprout::container_range_traits<Container>::range_index_of(cont, p);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
		range_index_of(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
			return sprout::container_range_traits<Container>::range_index_of(cont, p);
		}
	}	// namespace container_detail

	//
	// index_of
	//
	//	effect:
	//		ADL callable range_index_of(cont, p) -> range_index_of(cont, p)
	//		otherwise -> sprout::container_range_traits<Container>::range_index_of(cont, p)
	//		[default]
	//			callable cont.index_of(p) -> cont.index_of(p)
	//			otherwise -> *next(begin(cont), p)
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::size_type
	index_of(Container& cont, typename sprout::container_traits<Container>::iterator p) {
		using sprout::container_detail::range_index_of;
		using sprout_adl::range_index_of;
		return range_index_of(cont, p);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
	index_of(Container const& cont, typename sprout::container_traits<Container const>::iterator p) {
		using sprout::container_detail::range_index_of;
		using sprout_adl::range_index_of;
		return range_index_of(cont, p);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::size_type
	index_of(T (& arr)[N], typename sprout::container_traits<T[N]>::iterator p) {
		return sprout::container_detail::range_index_of(arr, p);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::size_type
	index_of(T const (& arr)[N], typename sprout::container_traits<T const[N]>::iterator p) {
		return sprout::container_detail::range_index_of(arr, p);
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
