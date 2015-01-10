/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_AT_HPP
#define SPROUT_CONTAINER_AT_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_at(...);
}	// namespace sprout_adl

namespace sprout {
	namespace container_detail {
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
		range_at(Container& cont, typename sprout::container_traits<Container>::size_type i) {
			return sprout::container_range_traits<Container>::range_at(cont, i);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
		range_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
			return sprout::container_range_traits<Container>::range_at(cont, i);
		}
	}	// namespace container_detail

	//
	// at
	//
	//	effect:
	//		ADL callable range_at(cont, i) -> range_at(cont, i)
	//		otherwise -> sprout::container_range_traits<Container>::range_at(cont, i)
	//		[default]
	//			callable cont.at(i) -> cont.at(i)
	//			otherwise -> *next(begin(cont), i)
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	at(Container& cont, typename sprout::container_traits<Container>::size_type i) {
		using sprout::container_detail::range_at;
		using sprout_adl::range_at;
		return range_at(cont, i);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		using sprout::container_detail::range_at;
		using sprout_adl::range_at;
		return range_at(cont, i);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
	at(T (& arr)[N], typename sprout::container_traits<T[N]>::size_type i) {
		return sprout::container_detail::range_at(arr, i);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
	at(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
		return sprout::container_detail::range_at(arr, i);
	}

	//
	// cat
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	cat(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		return sprout::at(cont, i);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
	cat(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
		return sprout::at(arr, i);
	}
}	// namespace sprout

#include <sprout/container/container_range_traits.hpp>

#endif	// #ifndef SPROUT_CONTAINER_AT_HPP
