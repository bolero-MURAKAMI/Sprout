/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_DATA_HPP
#define SPROUT_CONTAINER_DATA_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// data
	//
	//	effect:
	//		sprout::container_range_traits<Container>::range_data(cont)
	//		[default]
	//			ADL callable range_data(cont) -> range_data(cont)
	//			[default]
	//				Container is T[N] -> pointer(cont)
	//				otherwise, Container is not const
	//					&& sprout::is_const_cast_convertible<const_pointer, pointer>
	//					&& callable sprout::as_const(cont).data()
	//					-> const_cast<pointer>(sprout::data(sprout::as_const(cont)))
	//				cont.data()
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::pointer
	data(Container& cont) {
		return sprout::container_range_traits<Container>::range_data(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
	data(Container const& cont) {
		return sprout::container_range_traits<Container>::range_data(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::pointer
	data(T (& arr)[N]) {
		return sprout::container_range_traits<T[N]>::range_data(arr);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::pointer
	data(T const (& arr)[N]) {
		return sprout::container_range_traits<T const[N]>::range_data(arr);
	}

	//
	// cdata
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
	cdata(Container const& cont) {
		return sprout::data(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::pointer
	cdata(T const (& arr)[N]) {
		return sprout::data(arr);
	}
}	// namespace sprout

#include <sprout/container/container_range_traits.hpp>

#endif	// #ifndef SPROUT_CONTAINER_DATA_HPP
