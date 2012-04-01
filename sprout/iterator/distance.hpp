#ifndef SPROUT_ITERATOR_DISTANCE_HPP
#define SPROUT_ITERATOR_DISTANCE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>

namespace sprout {
	namespace detail {
		// Copyright (C) 2011 RiSK (sscrisk)

		template<typename Iterator>
		SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type
		distance(Iterator first, Iterator last) {
			return first == last ? 0
				: 1 + sprout::detail::distance(sprout::next(first), last)
				;
		}
		template<typename Iterator>
		SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type
		distance_impl(Iterator first, Iterator last) {
			using sprout::detail::distance;
			return distance(first, last);
		}
	}	// namespace detail
	//
	// distance
	//
	template<typename Iterator>
	SPROUT_CONSTEXPR typename std::iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last) {
		return sprout::detail::distance_impl(first, last);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_DISTANCE_HPP
