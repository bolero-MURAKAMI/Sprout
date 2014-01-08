/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP
#define SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// container_range_traits
	//
	template<typename Container>
	struct container_range_traits {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
		range_begin(Container& cont) {
			return cont.begin();
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_begin(Container const& cont) {
			return cont.begin();
		}

		static SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
		range_end(Container& cont) {
			return cont.end();
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_end(Container const& cont) {
			return cont.end();
		}
	};
	template<typename Container>
	struct container_range_traits<Container const> {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_begin(Container const& cont) {
			return sprout::container_range_traits<Container>::range_begin(cont);
		}

		static SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_end(Container const& cont) {
			return sprout::container_range_traits<Container>::range_end(cont);
		}
	};

	template<typename T, std::size_t N>
	struct container_range_traits<T[N]> {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
		range_begin(T (& arr)[N]) {
			typedef typename sprout::container_traits<T[N]>::iterator type;
			return type(arr);
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_begin(T const (& arr)[N]) {
			typedef typename sprout::container_traits<T const[N]>::iterator type;
			return type(arr);
		}

		static SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
		range_end(T (& arr)[N]) {
			typedef typename sprout::container_traits<T[N]>::iterator type;
			return type(arr) + N;
		}
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_end(T const (& arr)[N]) {
			typedef typename sprout::container_traits<T const[N]>::iterator type;
			return type(arr) + N;
		}
	};
	template<typename T, std::size_t N>
	struct container_range_traits<T const[N]> {
	public:
		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
		range_begin(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_begin(arr);
		}

		static SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::const_iterator
		range_end(T const (& arr)[N]) {
			return sprout::container_range_traits<T[N]>::range_end(arr);
		}
	};
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_CONTAINER_RANGE_TRAITS_HPP
