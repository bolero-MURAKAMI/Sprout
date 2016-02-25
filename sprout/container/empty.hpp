/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_EMPTY_HPP
#define SPROUT_CONTAINER_EMPTY_HPP

#include <sprout/config.hpp>
#include <sprout/workaround/std/cstddef.hpp>
#include <sprout/container/traits_fwd.hpp>
#include <sprout/container/container_traits.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl range_empty(...);
}	// namespace sprout_adl

namespace sprout {
	namespace container_detail {
		template<typename Container>
		inline SPROUT_CONSTEXPR bool
		range_empty(Container const& cont) {
			return sprout::container_range_traits<Container>::range_empty(cont);
		}
	}	// namespace container_detail

	//
	// empty
	//
	//	effect:
	//		ADL callable range_empty(cont) -> range_empty(cont)
	//		otherwise -> sprout::container_range_traits<Container>::range_empty(cont)
	//		[default]
	//			callable cont.empty() -> cont.empty()
	//			otherwise -> size(cont) == 0
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR bool
	empty(Container const& cont) {
		using sprout::container_detail::range_empty;
		using sprout_adl::range_empty;
		return range_empty(cont);
	}
	template<typename T, std::size_t N>
	inline SPROUT_CONSTEXPR bool
	empty(T const (& arr)[N]) {
		return sprout::container_detail::range_empty(arr);
	}
}	// namespace sprout

#include <sprout/container/container_range_traits.hpp>

#endif	// #ifndef SPROUT_CONTAINER_EMPTY_HPP
