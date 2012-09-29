#ifndef SPROUT_ITERATOR_DISTANCE_HPP
#define SPROUT_ITERATOR_DISTANCE_HPP

#include <iterator>
#include <sprout/config.hpp>
#include <sprout/iterator/next.hpp>
#include <sprout/adl/not_found.hpp>

namespace sprout_adl {
	sprout::not_found_via_adl iterator_distance(...);
}	// namespace sprout_adl

namespace sprout {
	namespace iterator_detail {
		// Copyright (C) 2011 RiSK (sscrisk)

		template<typename InputIterator>
		inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
		iterator_distance(InputIterator first, InputIterator last) {
			return first == last ? 0
				: 1 + sprout::iterator_detail::iterator_distance(sprout::next(first), last)
				;
		}
	}	// namespace iterator_detail
}	// namespace sprout

namespace sprout_iterator_detail {
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {
		using sprout::iterator_detail::iterator_distance;
		using sprout_adl::iterator_distance;
		return iterator_distance(first, last);
	}
}	// namespace sprout_iterator_detail

namespace sprout {
	//
	// distance
	//
	template<typename InputIterator>
	inline SPROUT_CONSTEXPR typename std::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {
		return sprout_iterator_detail::distance(first, last);
	}
}	// namespace sprout

#endif	// #ifndef SPROUT_ITERATOR_DISTANCE_HPP
