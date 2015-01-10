/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
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
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_back(...);
}	// namespace sprout_adl

namespace sprout {
	namespace container_detail {
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
		range_back(Container& cont) {
			return sprout::container_range_traits<Container>::range_back(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
		range_back(Container const& cont) {
			return sprout::container_range_traits<Container>::range_back(cont);
		}
	}	// namespace container_detail

	//
	// back
	//
	//	effect:
	//		ADL callable range_back(cont) -> range_back(cont)
	//		otherwise -> sprout::container_range_traits<Container>::range_back(cont)
	//		[default]
	//			callable cont.back() -> cont.back()
	//			otherwise -> *prev(end(cont))
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	back(Container& cont) {
		using sprout::container_detail::range_back;
		using sprout_adl::range_back;
		return range_back(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	back(Container const& cont) {
		using sprout::container_detail::range_back;
		using sprout_adl::range_back;
		return range_back(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
	back(T (& arr)[N]) {
		return sprout::container_detail::range_back(arr);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
	back(T const (& arr)[N]) {
		return sprout::container_detail::range_back(arr);
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
