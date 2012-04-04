#ifndef SPROUT_ALGORITHM_ADJACENT_FIND_HPP
#define SPROUT_ALGORITHM_ADJACENT_FIND_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/operation.hpp>
#include HDR_FUNCTIONAL_SSCRISK_CEL_OR_SPROUT

namespace sprout {
	// Copyright (C) 2011 RiSK (sscrisk)

	// 25.2.8 Adjacent find
	template<typename ForwardIterator, typename BinaryPredicate>
	inline SPROUT_CONSTEXPR ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred) {
		return first == last || sprout::next(first) == last ? last
			: pred(*first, *(sprout::next(first))) != false ? first
			: sprout::adjacent_find(sprout::next(first), last, pred)
			;
	}

	template<typename ForwardIterator>
	inline SPROUT_CONSTEXPR ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
		return sprout::adjacent_find(
			first,
			last,
			NS_SSCRISK_CEL_OR_SPROUT::equal_to<typename std::iterator_traits<ForwardIterator>::value_type>()
			);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ALGORITHM_ADJACENT_FIND_HPP
