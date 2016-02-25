/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
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
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_nth(...);
}	// namespace sprout_adl

namespace sprout {
	namespace container_detail {
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
		range_nth(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return sprout::container_range_traits<Container>::range_nth(cont, i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_nth(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return sprout::container_range_traits<Container>::range_nth(cont, i);
		}
	}	// namespace container_detail

	//
	// nth
	//
	//	effect:
	//		ADL callable range_nth(cont, i) -> range_nth(cont, i)
	//		otherwise -> sprout::container_range_traits<Container>::range_nth(cont, i)
	//		[default]
	//			callable cont.nth(i) -> cont.nth(i)
	//			otherwise -> *next(begin(cont), i)
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	nth(Container& cont, typename sprout::container_traits<Container>::size_type i) {
		using sprout::container_detail::range_nth;
		using sprout_adl::range_nth;
		return range_nth(cont, i);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	nth(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		using sprout::container_detail::range_nth;
		using sprout_adl::range_nth;
		return range_nth(cont, i);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
	nth(T (& arr)[N], typename sprout::container_traits<T[N]>::size_type i) {
		return sprout::container_detail::range_nth(arr, i);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
	nth(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
		return sprout::container_detail::range_nth(arr, i);
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
