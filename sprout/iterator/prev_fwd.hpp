/*=============================================================================
  Copyright (c) 2011-2017 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_PREV_FWD_HPP
#define SPROUT_ITERATOR_PREV_FWD_HPP

#include <iterator>
#include <sprout/config.hpp>

namespace sprout {
	//
	// prev
	//
	template<typename BidirectionalIterator>
	inline SPROUT_CONSTEXPR BidirectionalIterator
	prev(BidirectionalIterator const& it);

	template<typename BidirectionalIterator>
	inline SPROUT_CONSTEXPR BidirectionalIterator
	prev(BidirectionalIterator const& it, typename std::iterator_traits<BidirectionalIterator>::difference_type n);
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_PREV_FWD_HPP
