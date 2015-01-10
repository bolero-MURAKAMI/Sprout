/*=============================================================================
  Copyright (c) 2011-2015 Bolero MURAKAMI
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
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_data(...);
}	// namespace sprout_adl

namespace sprout {
	namespace container_detail {
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::pointer
		range_data(Container& cont) {
			return sprout::container_range_traits<Container>::range_data(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
		range_data(Container const& cont) {
			return sprout::container_range_traits<Container>::range_data(cont);
		}
	}	// namespace container_detail

	//
	// data
	//
	//	effect:
	//		ADL callable range_data(cont) -> range_data(cont)
	//		otherwise -> sprout::container_range_traits<Container>::range_data(cont)
	//		[default]
	//			cont.data()
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::pointer
	data(Container& cont) {
		using sprout::container_detail::range_data;
		using sprout_adl::range_data;
		return range_data(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::pointer
	data(Container const& cont) {
		using sprout::container_detail::range_data;
		using sprout_adl::range_data;
		return range_data(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::pointer
	data(T (& arr)[N]) {
		return sprout::container_detail::range_data(arr);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::pointer
	data(T const (& arr)[N]) {
		return sprout::container_detail::range_data(arr);
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
