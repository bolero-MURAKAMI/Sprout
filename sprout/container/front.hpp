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
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_front(...);
}	// namespace sprout_adl

namespace sprout {
	namespace container_detail {
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
		range_front(Container& cont) {
			return sprout::container_range_traits<Container>::range_front(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
		range_front(Container const& cont) {
			return sprout::container_range_traits<Container>::range_front(cont);
		}
	}	// namespace container_detail

	//
	// front
	//
	//	effect:
	//		ADL callable range_front(cont) -> range_front(cont)
	//		otherwise -> sprout::container_range_traits<Container>::range_front(cont)
	//		[default]
	//			callable cont.front() -> cont.front()
	//			otherwise -> *begin(cont)
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	front(Container& cont) {
		using sprout::container_detail::range_front;
		using sprout_adl::range_front;
		return range_front(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	front(Container const& cont) {
		using sprout::container_detail::range_front;
		using sprout_adl::range_front;
		return range_front(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
	front(T (& arr)[N]) {
		return sprout::container_detail::range_front(arr);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
	front(T const (& arr)[N]) {
		return sprout::container_detail::range_front(arr);
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
