/*=============================================================================
  Copyright (c) 2011-2016 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_CONTAINER_RANGE_INDEX_CHECK_HPP
#define SPROUT_CONTAINER_RANGE_INDEX_CHECK_HPP

#include <stdexcept>
#include <sprout/config.hpp>
#include <sprout/container/range_functions_fwd.hpp>
#include <sprout/container/container_traits.hpp>

namespace sprout {
	//
	// range_index_check
	//
	template<typename Container>
	inline SPROUT_CONSTEXPR typename sprout::container_traits<Container const>::size_type
	range_index_check(Container const& cont, typename sprout::container_traits<Container const>::size_type i) {
		return i >= sprout::size(cont) ? throw std::out_of_range("range_index_check: index out of range")
			: i
			;
	}
}	// namespace sprout

#include <sprout/container/size.hpp>

#endif	// #ifndef SPROUT_CONTAINER_RANGE_INDEX_CHECK_HPP
