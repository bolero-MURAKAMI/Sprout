/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_STD_ARRAY_HPP
#define SPROUT_CONTAINER_STD_ARRAY_HPP

#include <array>
#include <utility>
#include <type_traits>
#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits.hpp>
#include <sprout/iterator/index_iterator.hpp>
#include <sprout/utility/forward.hpp>
#include <sprout/utility/as_const.hpp>
#include <sprout/memory/addressof.hpp>
#include <sprout/detail/functional/const_subscript.hpp>

namespace sprout {
	//
	// container_traits
	//
	template<typename T, std::size_t N>
	struct container_traits<std::array<T, N> >
		: public sprout::container_traits_default<std::array<T, N> >
	{
	public:
		typedef sprout::index_iterator<std::array<T, N>&, true, sprout::detail::const_subscript<> > iterator;
		typedef sprout::index_iterator<std::array<T, N> const&, true, sprout::detail::const_subscript<> > const_iterator;
	};

	//
	// container_range_traits
	//
	template<typename T, std::size_t N>
	struct container_range_traits<std::array<T, N> >
		: public sprout::container_range_traits_default<std::array<T, N> >
	{
	public:
		// iterators:
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> >::iterator
		range_begin(std::array<T, N>& cont) {
			return typename sprout::container_traits<std::array<T, N> >::iterator(cont, 0);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> const>::iterator
		range_begin(std::array<T, N> const& cont) {
			return typename sprout::container_traits<std::array<T, N> const>::iterator(cont, 0);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> >::iterator
		range_end(std::array<T, N>& cont) {
			return typename sprout::container_traits<std::array<T, N> >::iterator(cont, cont.size());
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> const>::iterator
		range_end(std::array<T, N> const& cont) {
			return typename sprout::container_traits<std::array<T, N> const>::iterator(cont, cont.size());
		}
		// data access:
		static SPROUT_CONSTEXPR typename sprout::container_traits<std::array<T, N> const>::pointer
		range_data(std::array<T, N> const& cont) {
			return sprout::addressof(range_front(cont));
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_STD_ARRAY_HPP
