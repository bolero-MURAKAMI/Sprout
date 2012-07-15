#ifndef SPROUT_ITERATOR_DISTANCE_HPP
#define SPROUT_ITERATOR_DISTANCE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>

namespace sprout {
	namespace detail {
		// Copyright (C) 2011 RiSK (sscrisk)

		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last) {
			return first == last ? 0
				: 1 + sprout::detail::distance(sprout::next(first), last)
				;
		}
		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		distance_impl(InputIterator first, InputIterator last) {
			using sprout::detail::distance;
			return distance(first, last);
		}
	}	// namespace detail
	//
	// distance
	//
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {
		return sprout::detail::distance_impl(first, last);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_DISTANCE_HPP
