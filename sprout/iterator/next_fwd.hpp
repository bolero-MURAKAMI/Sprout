/*=============================================================================
  Copyright (c) 2011-2014 Bolero MURAKAMI
  https://github.com/bolero-MURAKAMI/Sprout

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef SPROUT_ITERATOR_NEXT_FWD_HPP
#define SPROUT_ITERATOR_NEXT_FWD_HPP

#include <iterator>
#include <sprout/config.hpp>

namespace sprout {
	//
	// next
	//
	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	next(ForwardIterator const& it);

	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator
	next(ForwardIterator const& it, typename std::iterator_traits<ForwardIterator>::difference_type n);
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_NEXT_FWD_HPP
