/*=============================================================================
  Copyright (c) 2011-2019 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_SUBSCRIPT_AT_HPP
#define SPROUT_CONTAINER_SUBSCRIPT_AT_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// subscript_at
	//
	//	effect:
	//		sprout::container_range_traits<Container>::range_subscript_at(cont, i)
	//		[default]
	//			ADL callable range_subscript_at(cont, i) -> range_subscript_at(cont, i)
	//			[default]
	//				Container is T[N] -> cont[i]
	//				otherwise, Container is not const
	//					&& sprout::is_const_reference_cast_convertible<const_reference, reference>
	//					&& (callable sprout::as_const(cont)[i]
	//						|| callable sprout::as_const(cont).begin()
	//						|| ADL(without sprout) callable begin(sprout::as_const(cont))
	//						)
	//					-> sprout::const_reference_cast<reference>(sprout::subscript_at(sprout::as_const(cont), i))
	//				otherwise, callable cont[i] -> cont[i]
	//				otherwise -> *sprout::next(sprout::begin(cont), i)
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::reference
	subscript_at(Container& cont, typename sprout::container_traits<Container>::size_type i) {
		return sprout::container_range_traits<Container>::range_subscript_at(cont, i);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	subscript_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		return sprout::container_range_traits<Container const>::range_subscript_at(cont, i);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::reference
	subscript_at(T (& arr)[N], typename sprout::container_traits<T[N]>::size_type i) {
		return sprout::container_range_traits<T[N]>::range_subscript_at(arr, i);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
	subscript_at(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
		return sprout::container_range_traits<T const[N]>::range_subscript_at(arr, i);
	}

	//
	// csubscript_at
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::reference
	csubscript_at(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		return sprout::subscript_at(cont, i);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::reference
	csubscript_at(T const (& arr)[N], typename sprout::container_traits<T const[N]>::size_type i) {
		return sprout::subscript_at(arr, i);
	}
}	// namespace sprout

#include <sprout/container/container_range_traits.hpp>

#endif	// #ifndef SPROUT_CONTAINER_SUBSCRIPT_AT_HPP
