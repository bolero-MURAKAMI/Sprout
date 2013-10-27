/*=============================================================================
  Copyright (c) 2011-2013 Bolero MURAKAMI
  Copyright (C) 2011 RiSK (sscrisk)
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ALGORITHM_MIN_HPP
#define SPROUT_ALGORITHM_MIN_HPP

#include <initializer_list>
#include <sprout/config.hpp>
#include <sprout/algorithm/detail/min.hpp>
#include <sprout/algorithm/min_element.hpp>
#include <sprout/iterator/ptr_index_iterator.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {

	// 25.4.7 Minimum and maximum
	template<typename T, typename Compare>
	inline SPROUT_INITIALIZER_LIST_CONSTEXPR T
	min(std::initializer_list<T> t, Compare comp) {
		return *sprout::min_element(sprout::ptr_index(t.begin(), 0), sprout::ptr_index(t.begin(), t.size()), comp);
	}

	template<typename T>
	inline SPROUT_INITIALIZER_LIST_CONSTEXPR T
	min(std::initializer_list<T> t) {
		return sprout::min(t, NS_SSCRISK_CEL_OR_SPROUT::less<T>());
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_MIN_HPP
