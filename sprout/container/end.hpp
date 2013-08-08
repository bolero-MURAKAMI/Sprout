/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_END_HPP
#define SPROUT_CONTAINER_END_HPP

#include <cstddef>
#include <sprout/config.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/container/container_range_traits.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_end(...);
}	// namespace sprout_adl

namespace sprout {
	namespace container_detail {
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
		range_end(Container& cont) {
			return sprout::container_range_traits<Container>::range_end(cont);
		}
		template<typename Container>
		inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
		range_end(Container const& cont) {
			return sprout::container_range_traits<Container>::range_end(cont);
		}
	}	// namespace container_detail

	//
	// end
	//
	//	effect:
	//		ADL callable range_end(cont) -> range_end(cont)
	//		otherwise -> sprout::container_range_traits<Container>::range_end(cont)
	//		[default]
	//			cont.end()
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container>::iterator
	end(Container& cont) {
		using sprout::container_detail::range_end;
		using sprout_adl::range_end;
		return range_end(cont);
	}
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	end(Container const& cont) {
		using sprout::container_detail::range_end;
		using sprout_adl::range_end;
		return range_end(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T[N]>::iterator
	end(T (& arr)[N]) {
		return sprout::container_detail::range_end(arr);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
	end(T const (& arr)[N]) {
		return sprout::container_detail::range_end(arr);
	}

	//
	// cend
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::iterator
	cend(Container const& cont) {
		return sprout::end(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<T const[N]>::iterator
	cend(T const (& arr)[N]) {
		return sprout::end(arr);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_CONTAINER_END_HPP
