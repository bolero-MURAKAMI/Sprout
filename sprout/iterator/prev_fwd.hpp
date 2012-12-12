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
